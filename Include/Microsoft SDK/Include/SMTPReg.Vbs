'THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT 
'WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, 
'INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES 
'OF MERCHANTABILITY AND/OR FITNESS FOR A  PARTICULAR 
'PURPOSE

'------------------------------------------------------------------------------
'FILE DESCRIPTION: Script for registering for SMTP Protocol sinks. 
'
'File Name: smtpreg.vbs
' 
'
' Copyright (c) Microsoft Corporation 1993-1999. All rights reserved.
'------------------------------------------------------------------------------
Option Explicit

'
'
' the OnArrival event GUID
Const GUIDComCatOnArrival = "{ff3caa23-00b9-11d2-9dfb-00C04FA322BA}"
' the SMTP source type
Const GUIDSourceType = "{FB65C4DC-E468-11D1-AA67-00C04FA345F6}"
' 
Const GUIDCat = "{871736c0-fd85-11d0-869a-00c04fd65616}"
Const GUIDSources = "{DBC71A31-1F4B-11d0-869D-80C04FD65616}"

' the SMTP service display name.  This is used to key which service to
' edit
Const szService = "smtpsvc"

' the event manager object.  This is used to communicate with the 
' event binding database.
Dim EventManager
Set EventManager = WScript.CreateObject("Event.Manager")

'
' register a new sink with event manager
'
' iInstance - the instance to work against
' szEvent - OnArrival
' szDisplayName - the display name for this new sink
' szProgID - the progid to call for this event
' szRule - the rule to set for this event
'
public sub RegisterSink(iInstance, szEvent, szDisplayName, szProgID, szRule)
	Dim SourceType
	Dim szSourceDisplayName
	Dim Source
	Dim Binding
	Dim GUIDComCat
	Dim PrioVal

	' figure out which event they are trying to register with and set
	' the comcat for this event in GUIDComCat
	select case LCase(szEvent)
		case "onarrival"
			GUIDComCat = GUIDComCatOnArrival
		case else
			WScript.echo "invalid event: " & szEvent
			exit sub
	end select
	' enumerate through each of the registered instances for the SMTP source
	' type and look for the display name that matches the instance display
	' name
	set SourceType = EventManager.SourceTypes(GUIDSourceType)
	szSourceDisplayName = szService & " " & iInstance
	for each Source in SourceType.Sources
		if Source.DisplayName = szSourceDisplayName then
			' we've found the desired instance.  now add a new binding
			' with the right event GUID.  by not specifying a GUID to the
			' Add method we get server events to create a new ID for this
			' event
			set Binding = Source.GetBindingManager.Bindings(GUIDComCat).Add("")
			' set the binding properties
			Binding.DisplayName = szDisplayName
			Binding.SinkClass = szProgID
			' register a rule with the binding
			Binding.SourceProperties.Add "Rule", szRule
			' register a priority with the binding
			PrioVal = GetNextPrio(Source, GUIDComCat)
			If PrioVal < 0 then
				WScript.Echo "assigning priority to default value (24575)"
				Binding.SourceProperties.Add "Priority", 24575
			else	
				WScript.Echo "assigning priority (" & PrioVal & " of 32767)"
				Binding.SourceProperties.Add "Priority", PrioVal
			end if
			' save the binding
			Binding.Save
			WScript.Echo "registered " & szDisplayName
			exit sub
		end if
	next
end sub

'
' iterate through the bindings in a source, find the binding
' with the lowest priority, and return the next priority value.
' If the next value exceeds the range, return -1.
'
public function GetNextPrio(oSource, GUIDComCat)
	' it's possible that priority values will not be
	' numbers, so we add error handling for this case
	on error resume next

	Dim Bindings
	Dim Binding
	Dim nLowestPrio
	Dim nPrioVal
	nLowestPrio = 0
	set Bindings = oSource.GetBindingManager.Bindings(GUIDComCat)
	' if the bindings collection is empty, then this is the first
	' sink.  It gets the highest priority (0).
	if Bindings.Count = 0 then
		GetNextPrio = 0
	else
		' get the lowest existing priority value
		for each Binding in Bindings
			nPrioVal = Binding.SourceProperties.Item("Priority")
			if CInt(nPrioVal) > nLowestPrio then
				if err.number = 13 then
					err.clear
				else
					nLowestPrio = CInt(nPrioVal)
				end if
			end if
		next 
		' assign priority values in increments of 10 so priorities
		' can be shuffled later without the need to reorder all
		' binding priorities.  Valid priority values are 0 - 32767
		if nLowestPrio + 10 > 32767 then
			GetNextPrio = -1
		else
			GetNextPrio = nLowestPrio + 10
		end if
	end if
end function  

'
' check for a previously registered sink with the passed in name
'
' iInstance - the instance to work against
' szEvent - OnArrival
' szDisplayName - the display name of the event to check
' bCheckError - Any errors returned
public sub CheckSink(iInstance, szEvent, szDisplayName, bCheckError)
	Dim SourceType
	Dim GUIDComCat
	Dim szSourceDisplayName
	Dim Source
	Dim Bindings
	Dim Binding

	bCheckError = FALSE
	select case LCase(szEvent)
		case "onarrival"
			GUIDComCat = GUIDComCatOnArrival
		case else
			WScript.echo "invalid event: " & szEvent
			exit sub
	end select

	' find the source for this instance
	set SourceType = EventManager.SourceTypes(GUIDSourceType)
	szSourceDisplayName = szService & " " & iInstance
	for each Source in SourceType.Sources
		if Source.DisplayName = szSourceDisplayName then
			' find the binding by display name.  to do this we enumerate
			' all of the bindings and try to match on the display name
			set Bindings = Source.GetBindingManager.Bindings(GUIDComCat)
			for each Binding in Bindings
				if Binding.DisplayName = szDisplayName then
					' we've found the binding, now log an error
					WScript.Echo "Binding with the name " & szDisplayName & " already exists"
					exit sub 
				end if
			next
		end if
	next
	bCheckError = TRUE
end sub

'
' unregister a previously registered sink
'
' iInstance - the instance to work against
' szEvent - OnArrival
' szDisplayName - the display name of the event to remove
'
public sub UnregisterSink(iInstance, szEvent, szDisplayName)
	Dim SourceType
	Dim GUIDComCat
	Dim szSourceDisplayName
	Dim Source
	Dim Bindings
	Dim Binding

	select case LCase(szEvent)
		case "onarrival"
			GUIDComCat = GUIDComCatOnArrival
		case else
			WScript.echo "invalid event: " & szEvent
			exit sub
	end select

	' find the source for this instance
	set SourceType = EventManager.SourceTypes(GUIDSourceType)
	szSourceDisplayName = szService & " " & iInstance
	for each Source in SourceType.Sources
		if Source.DisplayName = szSourceDisplayName then
			' find the binding by display name.  to do this we enumerate
			' all of the bindings and try to match on the display name
			set Bindings = Source.GetBindingManager.Bindings(GUIDComCat)
			for each Binding in Bindings
				if Binding.DisplayName = szDisplayName then
					' we've found the binding, now remove it
					Bindings.Remove(Binding.ID)
					WScript.Echo "removed " & szDisplayName & " " & Binding.ID
				end if
			next
		end if
	next
end sub

'
' add or remove a property from the source or sink propertybag for an event
'
' iInstance - the SMTP instance to edit
' szEvent - the event type (OnArrival)
' szDisplayName - the display name of the event
' szPropertyBag - the property bag to edit ("source" or "sink")
' szOperation - "add" or "remove"
' szPropertyName - the name to edit in the property bag
' szPropertyValue - the value to assign to the name (ignored for remove)
'
public sub EditProperty(iInstance, szEvent, szDisplayName, szPropertyBag, szOperation, szPropertyName, szPropertyValue)
	Dim SourceType
	Dim GUIDComCat
	Dim szSourceDisplayName
	Dim Source
	Dim Bindings
	Dim Binding
	Dim PropertyBag

	select case LCase(szEvent)
		case "onarrival"
			GUIDComCat = GUIDComCatOnArrival
		case else
			WScript.echo "invalid event: " & szEvent
			exit sub
	end select

	' find the source for this instance
	set SourceType = EventManager.SourceTypes(GUIDSourceType)
	szSourceDisplayName = szService & " " & iInstance
	for each Source in SourceType.Sources
		if Source.DisplayName = szSourceDisplayName then
			set Bindings = Source.GetBindingManager.Bindings(GUIDComCat)
			' find the binding by display name.  to do this we enumerate
			' all of the bindings and try to match on the display name
			for each Binding in Bindings
				if Binding.DisplayName = szDisplayName then
					' figure out which set of properties we want to modify
					' based on the szPropertyBag parameter
					select case LCase(szPropertyBag)
						case "source"
							set PropertyBag = Binding.SourceProperties
						case "sink"
							set PropertyBag = Binding.SinkProperties
						case else
							WScript.echo "invalid propertybag: " & szPropertyBag
							exit sub
					end select
					' figure out what operation we want to perform
					select case LCase(szOperation)
						case "remove"
							' they want to remove szPropertyName from the
							' property bag
							PropertyBag.Remove szPropertyName
							WScript.echo "removed property " & szPropertyName
						case "add"
							' add szPropertyName to the property bag and 
							' set its value to szValue.  if this value
							' already exists then this will change  the value
							' it to szValue.
							PropertyBag.Add szPropertyName, szPropertyValue
							WScript.echo "set property " & szPropertyName & " to " & szPropertyValue
						case else
							WScript.echo "invalid operation: " & szOperation
							exit sub
					end select
					' save the binding
					Binding.Save
				end if
			next
		end if
	next
end sub

'
' this helper function takes an IEventSource object and a event category
' and dumps all of the bindings for this category under the source
'
' Source - the IEventSource object to display the bindings for
' GUIDComCat - the event category to display the bindings for
'
public sub DisplaySinksHelper(Source, GUIDComCat)
	Dim Binding
	Dim propval
	' walk each of the registered bindings for this component category
	for each Binding in Source.GetBindingManager.Bindings(GUIDComCat)
		' display the binding properties
		WScript.echo "    Binding " & Binding.ID & " {"
		WScript.echo "      DisplayName = " & Binding.DisplayName
		WScript.echo "      SinkClass = " & Binding.SinkClass
		if Binding.Enabled = True then
			WScript.echo "      Status = Enabled"
		else
			WScript.echo "      Status = Disabled"
		end if

		' walk each of the source properties and display them
		WScript.echo "      SourceProperties {"
		for each propval in Binding.SourceProperties
			WScript.echo "        " & propval & " = " & Binding.SourceProperties.Item(propval)
		next
		WScript.echo "      }"

		' walk each of the sink properties and display them
		WScript.echo "      SinkProperties {"
		for each Propval in Binding.SinkProperties
			WScript.echo "        " & propval & " = " & Binding.SinkProperties.Item(Propval)
		next
		WScript.echo "      }"
		WScript.echo "    }"
	next
end sub

'
' dumps all of the information in the binding database related to SMTP
'
public sub DisplaySinks
	Dim SourceType
	Dim Source

	' look for each of the sources registered for the SMTP source type
	set SourceType = EventManager.SourceTypes(GUIDSourceType)
	for each Source in SourceType.Sources
		' display the source properties
		WScript.echo "Source " & Source.ID & " {"
		WScript.echo "  DisplayName = " & Source.DisplayName
		' display all of the sinks registered for the OnArrival event
		WScript.echo "  OnArrival Sinks {"
		call DisplaySinksHelper(Source, GUIDComCatOnArrival)
		WScript.echo "  }"
	next
end sub

'
' enable/disable a registered sink
'
' iInstance - the instance to work against
' szEvent - OnArrival
' szDisplayName - the display name for this new sink
'
public sub SetSinkEnabled(iInstance, szEvent, szDisplayName, szEnable)
	Dim SourceType
	Dim GUIDComCat
	Dim szSourceDisplayName
	Dim Source
	Dim Bindings
	Dim Binding

	select case LCase(szEvent)
		case "onarrival"
			GUIDComCat = GUIDComCatOnArrival
		case else
			WScript.echo "invalid event: " + szEvent
			exit sub
	end select

	' find the source for this instance
	set SourceType = EventManager.SourceTypes(GUIDSourceType)
	szSourceDisplayName = szService + " " + iInstance
	for each Source in SourceType.Sources
		if Source.DisplayName = szSourceDisplayName then
			' find the binding by display name.  to do this we enumerate
			' all of the bindings and try to match on the display name
			set Bindings = Source.GetBindingManager.Bindings(GUIDComCat)
			for each Binding in Bindings
				if Binding.DisplayName = szDisplayName then
					' we've found the binding, now enable/disable it
					' we don't need "case else' because szEnable's value
					' is set internally, not by users
					select case LCase(szEnable)
						case "true"
							Binding.Enabled = True
							Binding.Save
							WScript.Echo "enabled " + szDisplayName + " " + Binding.ID
						case "false"
							Binding.Enabled = False
							Binding.Save
							WScript.Echo "disabled " + szDisplayName + " " + Binding.ID
						end select
				end if
			next
		end if
	next
end sub

' 
' display usage information for this script
'
public sub DisplayUsage
	WScript.echo "usage: cscript smtpreg.vbs <command> <arguments>"
	WScript.echo "  commands:"
	WScript.echo "    /add <Instance> <Event> <DisplayName> <SinkClass> <Rule>"
	WScript.echo "    /remove <Instance> <Event> <DisplayName>"
	WScript.echo "    /setprop <Instance> <Event> <DisplayName> <PropertyBag> <PropertyName> "
	WScript.echo "             <PropertyValue>"
	WScript.echo "    /delprop <Instance> <Event> <DisplayName> <PropertyBag> <PropertyName>"
	WScript.echo "    /enable <Instance> <Event> <DisplayName>"
	WScript.echo "    /disable <Instance> <Event> <DisplayName>"
	WScript.echo "    /enum"
	WScript.echo "  arguments:"
	WScript.echo "    <Instance> is the SMTP instance to work against"
	WScript.echo "    <Event> can be OnArrival"
	WScript.echo "    <DisplayName> is the display name of the event to edit"
	WScript.echo "    <SinkClass> is the sink class for the event"
	WScript.echo "    <Rule> is the rule to use for the event"	
	WScript.echo "    <PropertyBag> can be Source or Sink"
	WScript.echo "    <PropertyName> is the name of the property to edit"
	WScript.echo "    <PropertyValue> is the value to assign to the property"
end sub


Dim iInstance
Dim szEvent
Dim szDisplayName
Dim szSinkClass
Dim szRule
Dim szPropertyBag
Dim szPropertyName
Dim szPropertyValue
dim bCheck

'
' this is the main body of our script.  it reads the command line parameters
' specified and then calls the appropriate function to perform the operation
'
if WScript.Arguments.Count = 0 then
	call DisplayUsage
else 
	Select Case LCase(WScript.Arguments(0))
		Case "/add"
			if not WScript.Arguments.Count = 6 then
				call DisplayUsage
			else
				iInstance = WScript.Arguments(1)
				szEvent = WScript.Arguments(2)
				szDisplayName = WScript.Arguments(3)
				szSinkClass = WScript.Arguments(4)
				szRule = WScript.Arguments(5)
				call CheckSink(iInstance, szEvent, szDisplayName, bCheck)
				if bCheck = TRUE then
					call RegisterSink(iInstance, szEvent, szDisplayName, szSinkClass, szRule)
				End if
			end if
		Case "/remove"
			if not WScript.Arguments.Count = 4 then
				call DisplayUsage
			else
				iInstance = WScript.Arguments(1)
				szEvent = WScript.Arguments(2)
				szDisplayName = WScript.Arguments(3)
				call UnregisterSink(iInstance, szEvent, szDisplayName)
			end if	
		Case "/setprop"
			if not WScript.Arguments.Count = 7 then
				call DisplayUsage
			else
				iInstance = WScript.Arguments(1)
				szEvent = WScript.Arguments(2)
				szDisplayName = WScript.Arguments(3)
				szPropertyBag = WScript.Arguments(4)
				szPropertyName = WScript.Arguments(5)
				szPropertyValue = WScript.Arguments(6)
				call EditProperty(iInstance, szEvent, szDisplayName, szPropertyBag, "add", szPropertyName, szPropertyValue)
			end if
		Case "/delprop"
			if not WScript.Arguments.Count = 6 then
				call DisplayUsage
			else
				iInstance = WScript.Arguments(1)
				szEvent = WScript.Arguments(2)
				szDisplayName = WScript.Arguments(3)
				szPropertyBag = WScript.Arguments(4)
				szPropertyName = WScript.Arguments(5)
				call EditProperty(iInstance, szEvent, szDisplayName, szPropertyBag, "remove", szPropertyName, "")		
			end if
		Case "/enable"
			if not WScript.Arguments.Count = 4 then
				call DisplayUsage
			else
				iInstance = WScript.Arguments(1)
				szEvent = WScript.Arguments(2)
				szDisplayName = WScript.Arguments(3)
				call SetSinkEnabled(iInstance, szEvent, szDisplayName, "True")
			end if
		Case "/disable"
			if not WScript.Arguments.Count = 4 then
				call DisplayUsage
			else
				iInstance = WScript.Arguments(1)
				szEvent = WScript.Arguments(2)
				szDisplayName = WScript.Arguments(3)
				call SetSinkEnabled(iInstance, szEvent, szDisplayName, "False")
			end if
		Case "/enum"
			if not WScript.Arguments.Count = 1 then
				call DisplayUsage
			else
				call DisplaySinks
			end if
		Case Else
			call DisplayUsage
	End Select
end if

'' SIG '' Begin signature block
'' SIG '' MIIj7AYJKoZIhvcNAQcCoIIj3TCCI9kCAQExCzAJBgUr
'' SIG '' DgMCGgUAMGcGCisGAQQBgjcCAQSgWTBXMDIGCisGAQQB
'' SIG '' gjcCAR4wJAIBAQQQTvApFpkntU2P5azhDxfrqwIBAAIB
'' SIG '' AAIBAAIBAAIBADAhMAkGBSsOAwIaBQAEFI3Vwo/zZkp/
'' SIG '' vqByjbmIq6ZOYpW3oIIe4TCCBBIwggL6oAMCAQICDwDB
'' SIG '' AIs8PIgR0T72Y+zfQDANBgkqhkiG9w0BAQQFADBwMSsw
'' SIG '' KQYDVQQLEyJDb3B5cmlnaHQgKGMpIDE5OTcgTWljcm9z
'' SIG '' b2Z0IENvcnAuMR4wHAYDVQQLExVNaWNyb3NvZnQgQ29y
'' SIG '' cG9yYXRpb24xITAfBgNVBAMTGE1pY3Jvc29mdCBSb290
'' SIG '' IEF1dGhvcml0eTAeFw05NzAxMTAwNzAwMDBaFw0yMDEy
'' SIG '' MzEwNzAwMDBaMHAxKzApBgNVBAsTIkNvcHlyaWdodCAo
'' SIG '' YykgMTk5NyBNaWNyb3NvZnQgQ29ycC4xHjAcBgNVBAsT
'' SIG '' FU1pY3Jvc29mdCBDb3Jwb3JhdGlvbjEhMB8GA1UEAxMY
'' SIG '' TWljcm9zb2Z0IFJvb3QgQXV0aG9yaXR5MIIBIjANBgkq
'' SIG '' hkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAqQK9wXDmO/JO
'' SIG '' Gyifl3heMOqiqY0lX/j+lUyjt/6doiA+fFGim6KPYDJr
'' SIG '' 0UJkee6sdslU2vLrnIYcj5+EZrPFa3piI9YdPN4PAZLo
'' SIG '' lsS/LWaammgmmdA6LL8MtVgmwUbnCj44liypKDmo7EmD
'' SIG '' QuOED7uabFVhrIJ8oWAtd0zpmbRkO5pQHDEIJBSfqeeR
'' SIG '' KxjmPZhjFGBYBWWfHTdSh/en75QCxhvTv1VFs4mAvzrs
'' SIG '' VJROrv2nem10Tq8YzJYJKCEAV5BgaTe7SxIHPFb/W/uk
'' SIG '' ZgoIptKBVlfvtjteFoF3BNr2vq6Alf6wzX/WpxpyXDzK
'' SIG '' vPAIoyIwswaFybMgdxOF3wIDAQABo4GoMIGlMIGiBgNV
'' SIG '' HQEEgZowgZeAEFvQcO9pcp4jUX4Usk2O/8uhcjBwMSsw
'' SIG '' KQYDVQQLEyJDb3B5cmlnaHQgKGMpIDE5OTcgTWljcm9z
'' SIG '' b2Z0IENvcnAuMR4wHAYDVQQLExVNaWNyb3NvZnQgQ29y
'' SIG '' cG9yYXRpb24xITAfBgNVBAMTGE1pY3Jvc29mdCBSb290
'' SIG '' IEF1dGhvcml0eYIPAMEAizw8iBHRPvZj7N9AMA0GCSqG
'' SIG '' SIb3DQEBBAUAA4IBAQCV6AvAjfOXGDXtuAEk2HcR81xg
'' SIG '' Mp+eC8s+BZGIj8k65iHy8FeTLLWgR8hi7/zXzDs7Wqk2
'' SIG '' VGn+JG0/ycyq3gV83TGNPZ8QcGq7/hJPGGnA/NBD4xFa
'' SIG '' IE/qYnuvqhnIKzclLb5loRKKJQ9jo/dUHPkhydYV81Ks
'' SIG '' bkMyB/2CF/jlZ2wNUfa98VLHvefEMPwgMQmIHZUpGk3V
'' SIG '' HQKl8YDgA7Rb9LHdyFfuZUnHUlS2tAMoEv+Q1vAIj364
'' SIG '' l8WrNyzkeuSod+N2oADQaj/B0jaK4EESqDVqG2rbNeHU
'' SIG '' HATkqEUEyFozOG5NHA1itwqijNPVVD9GzRxVpnDbEjqH
'' SIG '' k3Wfp9KgMIIEEjCCAvqgAwIBAgIPAMEAizw8iBHRPvZj
'' SIG '' 7N9AMA0GCSqGSIb3DQEBBAUAMHAxKzApBgNVBAsTIkNv
'' SIG '' cHlyaWdodCAoYykgMTk5NyBNaWNyb3NvZnQgQ29ycC4x
'' SIG '' HjAcBgNVBAsTFU1pY3Jvc29mdCBDb3Jwb3JhdGlvbjEh
'' SIG '' MB8GA1UEAxMYTWljcm9zb2Z0IFJvb3QgQXV0aG9yaXR5
'' SIG '' MB4XDTk3MDExMDA3MDAwMFoXDTIwMTIzMTA3MDAwMFow
'' SIG '' cDErMCkGA1UECxMiQ29weXJpZ2h0IChjKSAxOTk3IE1p
'' SIG '' Y3Jvc29mdCBDb3JwLjEeMBwGA1UECxMVTWljcm9zb2Z0
'' SIG '' IENvcnBvcmF0aW9uMSEwHwYDVQQDExhNaWNyb3NvZnQg
'' SIG '' Um9vdCBBdXRob3JpdHkwggEiMA0GCSqGSIb3DQEBAQUA
'' SIG '' A4IBDwAwggEKAoIBAQCpAr3BcOY78k4bKJ+XeF4w6qKp
'' SIG '' jSVf+P6VTKO3/p2iID58UaKboo9gMmvRQmR57qx2yVTa
'' SIG '' 8uuchhyPn4Rms8VremIj1h083g8BkuiWxL8tZpqaaCaZ
'' SIG '' 0Dosvwy1WCbBRucKPjiWLKkoOajsSYNC44QPu5psVWGs
'' SIG '' gnyhYC13TOmZtGQ7mlAcMQgkFJ+p55ErGOY9mGMUYFgF
'' SIG '' ZZ8dN1KH96fvlALGG9O/VUWziYC/OuxUlE6u/ad6bXRO
'' SIG '' rxjMlgkoIQBXkGBpN7tLEgc8Vv9b+6RmCgim0oFWV++2
'' SIG '' O14WgXcE2va+roCV/rDNf9anGnJcPMq88AijIjCzBoXJ
'' SIG '' syB3E4XfAgMBAAGjgagwgaUwgaIGA1UdAQSBmjCBl4AQ
'' SIG '' W9Bw72lyniNRfhSyTY7/y6FyMHAxKzApBgNVBAsTIkNv
'' SIG '' cHlyaWdodCAoYykgMTk5NyBNaWNyb3NvZnQgQ29ycC4x
'' SIG '' HjAcBgNVBAsTFU1pY3Jvc29mdCBDb3Jwb3JhdGlvbjEh
'' SIG '' MB8GA1UEAxMYTWljcm9zb2Z0IFJvb3QgQXV0aG9yaXR5
'' SIG '' gg8AwQCLPDyIEdE+9mPs30AwDQYJKoZIhvcNAQEEBQAD
'' SIG '' ggEBAJXoC8CN85cYNe24ASTYdxHzXGAyn54Lyz4FkYiP
'' SIG '' yTrmIfLwV5MstaBHyGLv/NfMOztaqTZUaf4kbT/JzKre
'' SIG '' BXzdMY09nxBwarv+Ek8YacD80EPjEVogT+pie6+qGcgr
'' SIG '' NyUtvmWhEoolD2Oj91Qc+SHJ1hXzUqxuQzIH/YIX+OVn
'' SIG '' bA1R9r3xUse958Qw/CAxCYgdlSkaTdUdAqXxgOADtFv0
'' SIG '' sd3IV+5lScdSVLa0AygS/5DW8AiPfriXxas3LOR65Kh3
'' SIG '' 43agANBqP8HSNorgQRKoNWobats14dQcBOSoRQTIWjM4
'' SIG '' bk0cDWK3CqKM09VUP0bNHFWmcNsSOoeTdZ+n0qAwggRg
'' SIG '' MIIDTKADAgECAgouqxHcUP9cncvAMAkGBSsOAwIdBQAw
'' SIG '' cDErMCkGA1UECxMiQ29weXJpZ2h0IChjKSAxOTk3IE1p
'' SIG '' Y3Jvc29mdCBDb3JwLjEeMBwGA1UECxMVTWljcm9zb2Z0
'' SIG '' IENvcnBvcmF0aW9uMSEwHwYDVQQDExhNaWNyb3NvZnQg
'' SIG '' Um9vdCBBdXRob3JpdHkwHhcNMDcwODIyMjIzMTAyWhcN
'' SIG '' MTIwODI1MDcwMDAwWjB5MQswCQYDVQQGEwJVUzETMBEG
'' SIG '' A1UECBMKV2FzaGluZ3RvbjEQMA4GA1UEBxMHUmVkbW9u
'' SIG '' ZDEeMBwGA1UEChMVTWljcm9zb2Z0IENvcnBvcmF0aW9u
'' SIG '' MSMwIQYDVQQDExpNaWNyb3NvZnQgQ29kZSBTaWduaW5n
'' SIG '' IFBDQTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoC
'' SIG '' ggEBALd5fdZds0U5qDSsMdr5JTVJd8D7H57HRXHv0Ubo
'' SIG '' 1IzDa0xSYvSZAsNN2ElsLyQ+Zb/OI7cLSLd/dd1FvaqP
'' SIG '' DlDFJSvyoOcNIx/RQST6YpnPGUWlk0ofmc2zLyLDSi18
'' SIG '' b9kVHjuMORA53b0p9GY7LQEy//4nSKa1bAGHnPu6smN/
'' SIG '' gvlcoIGEhY6w8riUo884plCFFyeHTt0w9gA99Mb5PYG+
'' SIG '' hu1sOacuNPa0Lq8KfWKReGacmHMNhq/yxPMguU8SjWPL
'' SIG '' LNkyRRnuu0qWO1BTGM5mUXmqrYfIVj6fglCIbgWxNcF7
'' SIG '' JL1SZj2ZTswrfjNuhEcG0Z7QSoYCboYApMCH31MCAwEA
'' SIG '' AaOB+jCB9zATBgNVHSUEDDAKBggrBgEFBQcDAzCBogYD
'' SIG '' VR0BBIGaMIGXgBBb0HDvaXKeI1F+FLJNjv/LoXIwcDEr
'' SIG '' MCkGA1UECxMiQ29weXJpZ2h0IChjKSAxOTk3IE1pY3Jv
'' SIG '' c29mdCBDb3JwLjEeMBwGA1UECxMVTWljcm9zb2Z0IENv
'' SIG '' cnBvcmF0aW9uMSEwHwYDVQQDExhNaWNyb3NvZnQgUm9v
'' SIG '' dCBBdXRob3JpdHmCDwDBAIs8PIgR0T72Y+zfQDAPBgNV
'' SIG '' HRMBAf8EBTADAQH/MB0GA1UdDgQWBBTMHc52AHBbr/Ha
'' SIG '' xE6aUUQuo0Rj8DALBgNVHQ8EBAMCAYYwCQYFKw4DAh0F
'' SIG '' AAOCAQEAe6uufkom8s68TnSiWCd0KnWzhv2rTJR4AE3p
'' SIG '' yusY3GnFDqJ88wJDxsqHzPhTzMKfvVZv8GNEqUQA7pbI
'' SIG '' mtUcuAufGQ2U19oerSl97+2mc6yP3jmOPZhqvDht0oiv
'' SIG '' I/3f6dZpCZGIvf7hALs08/d8+RASLgXrKZaTQmsocbc4
'' SIG '' j+AHDcldaM29gEFrZqi7t7uONMryAxB8evXS4ELfe/7h
'' SIG '' 4az+9t/VDbNw1pLjT7Y4onwt1D3bNAtiNwKfgWojifZc
'' SIG '' Y4+wWrs512CMVYQaM/U7mKCCDKJfi7Mst6Gly6vaILa/
'' SIG '' MBmFIBQNKrxS9EHgXjDjkihph8Fw4vOnq86AQnJ2DjCC
'' SIG '' BGowggNSoAMCAQICCmEPeE0AAAAAAAMwDQYJKoZIhvcN
'' SIG '' AQEFBQAweTELMAkGA1UEBhMCVVMxEzARBgNVBAgTCldh
'' SIG '' c2hpbmd0b24xEDAOBgNVBAcTB1JlZG1vbmQxHjAcBgNV
'' SIG '' BAoTFU1pY3Jvc29mdCBDb3Jwb3JhdGlvbjEjMCEGA1UE
'' SIG '' AxMaTWljcm9zb2Z0IENvZGUgU2lnbmluZyBQQ0EwHhcN
'' SIG '' MDcwODIzMDAyMzEzWhcNMDkwMjIzMDAzMzEzWjB0MQsw
'' SIG '' CQYDVQQGEwJVUzETMBEGA1UECBMKV2FzaGluZ3RvbjEQ
'' SIG '' MA4GA1UEBxMHUmVkbW9uZDEeMBwGA1UEChMVTWljcm9z
'' SIG '' b2Z0IENvcnBvcmF0aW9uMR4wHAYDVQQDExVNaWNyb3Nv
'' SIG '' ZnQgQ29ycG9yYXRpb24wggEiMA0GCSqGSIb3DQEBAQUA
'' SIG '' A4IBDwAwggEKAoIBAQCi2wqNz8LBSZvNqjo0rSNZa9ts
'' SIG '' viEit5TI6q6/xtUmwjIRi7zaXSz7NlYeFSuujw3dFKNu
'' SIG '' KEx/Fj9BrI1AsUaIDdmBlK2XBtBXRHZc6vH8DuJ/dKMz
'' SIG '' y3Tl7+NhoX4Dt0X/1T4S1bDKXg3Qe/K3Ew38YGoohXWM
'' SIG '' t628hegXtJC+9Ra2Yl3tEd867iFbi6+Ac8NF45WJd2Cb
'' SIG '' 5613wTeNMxQvE9tiya4aqU+YZ63UIDkwceCNZ0bixhz0
'' SIG '' DVB0QS/oBSRqIWtJsJLEsjnHQqVtXBhKq4/XjoM+eApH
'' SIG '' 2KSyhCPD4vJ7ZrFKdL0mQUucYRRgTjDIgvPQC3B87lVN
'' SIG '' d9IIVXaBAgMBAAGjgfgwgfUwDgYDVR0PAQH/BAQDAgbA
'' SIG '' MB0GA1UdDgQWBBTzIUCOfFH4VEuY5RfXaoM0BS4m6DAT
'' SIG '' BgNVHSUEDDAKBggrBgEFBQcDAzAfBgNVHSMEGDAWgBTM
'' SIG '' Hc52AHBbr/HaxE6aUUQuo0Rj8DBEBgNVHR8EPTA7MDmg
'' SIG '' N6A1hjNodHRwOi8vY3JsLm1pY3Jvc29mdC5jb20vcGtp
'' SIG '' L2NybC9wcm9kdWN0cy9DU1BDQS5jcmwwSAYIKwYBBQUH
'' SIG '' AQEEPDA6MDgGCCsGAQUFBzAChixodHRwOi8vd3d3Lm1p
'' SIG '' Y3Jvc29mdC5jb20vcGtpL2NlcnRzL0NTUENBLmNydDAN
'' SIG '' BgkqhkiG9w0BAQUFAAOCAQEAQFdvU2eeIIM0AQ7mF0s8
'' SIG '' revYgX/uDXl0d0+XRxjzABVpfttikKL9Z6Gc5Cgp+lXX
'' SIG '' mf5Qv14Js7mm7YLzmB5vWfr18eEM04sIPhYXINHAtUVH
'' SIG '' CCZgVwlLlPAIzLpNbvDiSBIoNYshct9ftq9pEiSU7uk0
'' SIG '' Cdt+bm+SClLKKkxJqjIshuihzF0mvLw84Fuygwu6NRxP
'' SIG '' hEVH/7uUoVkHqZbdeL1Xf6WnTszyrZyaQeLLXCQ+3H80
'' SIG '' R072z8h7neu2yZxjFFOvrZrv17/PoKGrlcp6K4cswMfZ
'' SIG '' /GwD2r84rfHRXBkXD8D3yoCmEAga3ZAj57ChTD7qsBEm
'' SIG '' eA7BLLmka8ePPDCCBJ0wggOFoAMCAQICCmFHUroAAAAA
'' SIG '' AAQwDQYJKoZIhvcNAQEFBQAweTELMAkGA1UEBhMCVVMx
'' SIG '' EzARBgNVBAgTCldhc2hpbmd0b24xEDAOBgNVBAcTB1Jl
'' SIG '' ZG1vbmQxHjAcBgNVBAoTFU1pY3Jvc29mdCBDb3Jwb3Jh
'' SIG '' dGlvbjEjMCEGA1UEAxMaTWljcm9zb2Z0IFRpbWVzdGFt
'' SIG '' cGluZyBQQ0EwHhcNMDYwOTE2MDE1MzAwWhcNMTEwOTE2
'' SIG '' MDIwMzAwWjCBpjELMAkGA1UEBhMCVVMxEzARBgNVBAgT
'' SIG '' Cldhc2hpbmd0b24xEDAOBgNVBAcTB1JlZG1vbmQxHjAc
'' SIG '' BgNVBAoTFU1pY3Jvc29mdCBDb3Jwb3JhdGlvbjEnMCUG
'' SIG '' A1UECxMebkNpcGhlciBEU0UgRVNOOkQ4QTktQ0ZDQy01
'' SIG '' NzlDMScwJQYDVQQDEx5NaWNyb3NvZnQgVGltZXN0YW1w
'' SIG '' aW5nIFNlcnZpY2UwggEiMA0GCSqGSIb3DQEBAQUAA4IB
'' SIG '' DwAwggEKAoIBAQCbbdyGUegyOzc6liWyz2/uYbVB0hg7
'' SIG '' Wp14Z7r4H9kIVZKIfuNBU/rsKFT+tdr+cDuVJ0h+Q6Ay
'' SIG '' LyaBSvICdnfIyan4oiFYfg29Adokxv5EEQU1OgGo6lQK
'' SIG '' MyyH0n5Bs+gJ2bC+45klprwl7dfTjtv0t20bSQvm08OH
'' SIG '' bu5GyX/zbevngx6oU0Y/yiR+5nzJLPt5FChFwE82a1Ma
'' SIG '' p4az5/zhwZ9RCdu8pbv+yocJ9rcyGb7hSlG8vHysLJVq
'' SIG '' l3PqclehnIuG2Ju9S/wnM8FtMqzgaBjYbjouIkPR+Y/t
'' SIG '' 8QABDWTAyaPdD/HI6VTKEf/ceCk+HaxYwNvfqtyuZRvT
'' SIG '' nbxnAgMBAAGjgfgwgfUwHQYDVR0OBBYEFE8YiYrSygB4
'' SIG '' xuxZDQ/9fMTBIoDeMB8GA1UdIwQYMBaAFG/oTj+XuTSr
'' SIG '' S4aPvJzqrDtBQ8bQMEQGA1UdHwQ9MDswOaA3oDWGM2h0
'' SIG '' dHA6Ly9jcmwubWljcm9zb2Z0LmNvbS9wa2kvY3JsL3By
'' SIG '' b2R1Y3RzL3RzcGNhLmNybDBIBggrBgEFBQcBAQQ8MDow
'' SIG '' OAYIKwYBBQUHMAKGLGh0dHA6Ly93d3cubWljcm9zb2Z0
'' SIG '' LmNvbS9wa2kvY2VydHMvdHNwY2EuY3J0MBMGA1UdJQQM
'' SIG '' MAoGCCsGAQUFBwMIMA4GA1UdDwEB/wQEAwIGwDANBgkq
'' SIG '' hkiG9w0BAQUFAAOCAQEANyce9YxA4PZlJj5kxJC8PuNX
'' SIG '' hd1DDUCEZ76HqCra3LQ2IJiOM3wuX+BQe2Ex8xoT3oS9
'' SIG '' 6mkcWHyzG5PhCCeBRbbUcMoUt1+6V+nUXtA7Q6q3P7ba
'' SIG '' YYtxz9R91Xtuv7TKWjCR39oKDqM1nyVhTsAydCt6BpRy
'' SIG '' AKwYnUvlnivFOlSspGDYp/ebf9mpbe1Ea7rc4BL68K2H
'' SIG '' DJVjCjIeiU7MzH6nN6X+X9hn+kZL0W0dp33SvgL/826C
'' SIG '' 84d0xGnluXDMS2WjBzWpRJ6EfTlu/hQFvRpQIbU+n/N3
'' SIG '' HI/Cmp1X4Wl9aeiDzwJvKiK7NzM6cvrWMB2RrfZQGusT
'' SIG '' 3jrFt1zNszCCBJ0wggOFoAMCAQICCmFJfO0AAAAAAAUw
'' SIG '' DQYJKoZIhvcNAQEFBQAweTELMAkGA1UEBhMCVVMxEzAR
'' SIG '' BgNVBAgTCldhc2hpbmd0b24xEDAOBgNVBAcTB1JlZG1v
'' SIG '' bmQxHjAcBgNVBAoTFU1pY3Jvc29mdCBDb3Jwb3JhdGlv
'' SIG '' bjEjMCEGA1UEAxMaTWljcm9zb2Z0IFRpbWVzdGFtcGlu
'' SIG '' ZyBQQ0EwHhcNMDYwOTE2MDE1NTIyWhcNMTEwOTE2MDIw
'' SIG '' NTIyWjCBpjELMAkGA1UEBhMCVVMxEzARBgNVBAgTCldh
'' SIG '' c2hpbmd0b24xEDAOBgNVBAcTB1JlZG1vbmQxHjAcBgNV
'' SIG '' BAoTFU1pY3Jvc29mdCBDb3Jwb3JhdGlvbjEnMCUGA1UE
'' SIG '' CxMebkNpcGhlciBEU0UgRVNOOjEwRDgtNTg0Ny1DQkY4
'' SIG '' MScwJQYDVQQDEx5NaWNyb3NvZnQgVGltZXN0YW1waW5n
'' SIG '' IFNlcnZpY2UwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAw
'' SIG '' ggEKAoIBAQDqugVjyNl5roREPqWzxO1MniTfOXYeCdYy
'' SIG '' Slh40ivZpQeQ7+c9+70mfKP75X1+Ms/ZPYs5N/L42Ds0
'' SIG '' FtSSgvs07GiFchqP4LhM4LiF8zMKAsGidnM1TF3xt+FK
'' SIG '' fR24lHjb/x6FFUJGcc5/J1cS0YNPO8/63vaL7T8A49Xe
'' SIG '' YfkXjUukgTz1aUDq4Ym/B0+6dHvpDOVH6qts8dVngQj4
'' SIG '' Fsp9E7tz4glM+mL77aA5mjr+6xHIYR5iWNgKVIPVO0tL
'' SIG '' 4lW9L2AajpIFQ9pd64IKI5cJoAUxZYuTTh5BIaKSkP1F
'' SIG '' REVvNbFFN61pqWX5NEOxF8I7OeEQjPIah+NUUB87nTGt
'' SIG '' AgMBAAGjgfgwgfUwHQYDVR0OBBYEFH5y8C4/VingJfdo
'' SIG '' uAH8S+F+z+M+MB8GA1UdIwQYMBaAFG/oTj+XuTSrS4aP
'' SIG '' vJzqrDtBQ8bQMEQGA1UdHwQ9MDswOaA3oDWGM2h0dHA6
'' SIG '' Ly9jcmwubWljcm9zb2Z0LmNvbS9wa2kvY3JsL3Byb2R1
'' SIG '' Y3RzL3RzcGNhLmNybDBIBggrBgEFBQcBAQQ8MDowOAYI
'' SIG '' KwYBBQUHMAKGLGh0dHA6Ly93d3cubWljcm9zb2Z0LmNv
'' SIG '' bS9wa2kvY2VydHMvdHNwY2EuY3J0MBMGA1UdJQQMMAoG
'' SIG '' CCsGAQUFBwMIMA4GA1UdDwEB/wQEAwIGwDANBgkqhkiG
'' SIG '' 9w0BAQUFAAOCAQEAaXqCCQwW0d7PRokuv9E0eoF/JyhB
'' SIG '' KvPTIZIOl61fU14p+e3BVEqoffcT0AsU+U3yhhUAbuOD
'' SIG '' HShFpyw5Mt1vmjda7iNSj1QDjT+nnGQ49jbIFEO2Oj6Y
'' SIG '' yQ3DcYEo82anMeJcXY/5UlLhXOuTkJ1pCUyJ0dF2TDQN
'' SIG '' auF8RKcrW4NUf0UkGSXEikbFJeMZgGkpFPYXxvAiLIFG
'' SIG '' Xiv0+abGdz4jb/mmZIWOomINqS0eqOWQPn//sI78l+zx
'' SIG '' /QSvzUnOWnSs+vMTHxs5zqO01rz0tO7IrfJWHvs88cjW
'' SIG '' KkS8v5w/fWYYzbIgYwrKQD1lMhl8srg9wSZITiIZmW6M
'' SIG '' MMHxkTCCBJ0wggOFoAMCAQICEGoLmU/AACWrEdtFH1h6
'' SIG '' Z6IwDQYJKoZIhvcNAQEFBQAwcDErMCkGA1UECxMiQ29w
'' SIG '' eXJpZ2h0IChjKSAxOTk3IE1pY3Jvc29mdCBDb3JwLjEe
'' SIG '' MBwGA1UECxMVTWljcm9zb2Z0IENvcnBvcmF0aW9uMSEw
'' SIG '' HwYDVQQDExhNaWNyb3NvZnQgUm9vdCBBdXRob3JpdHkw
'' SIG '' HhcNMDYwOTE2MDEwNDQ3WhcNMTkwOTE1MDcwMDAwWjB5
'' SIG '' MQswCQYDVQQGEwJVUzETMBEGA1UECBMKV2FzaGluZ3Rv
'' SIG '' bjEQMA4GA1UEBxMHUmVkbW9uZDEeMBwGA1UEChMVTWlj
'' SIG '' cm9zb2Z0IENvcnBvcmF0aW9uMSMwIQYDVQQDExpNaWNy
'' SIG '' b3NvZnQgVGltZXN0YW1waW5nIFBDQTCCASIwDQYJKoZI
'' SIG '' hvcNAQEBBQADggEPADCCAQoCggEBANw3bvuvyEJKcRjI
'' SIG '' zkg+U8D6qxS6LDK7Ek9SyIPtPjPZSTGSKLaRZOAfUIS6
'' SIG '' wkvRfwX473W+i8eo1a5pcGZ4J2botrfvhbnN7qr9EqQL
'' SIG '' WSIpL89A2VYEG3a1bWRtSlTb3fHev5+Dx4Dff0wCN5T1
'' SIG '' wJ4IVh5oR83ZwHZcL322JQS0VltqHGP/gHw87tUEJU05
'' SIG '' d3QHXcJc2IY3LHXJDuoeOQl8dv6dbG564Ow+j5eecQ5f
'' SIG '' Kk8YYmAyntKDTisiXGhFi94vhBBQsvm1Go1s7iWbE/jL
'' SIG '' ENeFDvSCdnM2xpV6osxgBuwFsIYzt/iUW4RBhFiFlG6w
'' SIG '' HyxIzG+cQ+Bq6H8mjmsCAwEAAaOCASgwggEkMBMGA1Ud
'' SIG '' JQQMMAoGCCsGAQUFBwMIMIGiBgNVHQEEgZowgZeAEFvQ
'' SIG '' cO9pcp4jUX4Usk2O/8uhcjBwMSswKQYDVQQLEyJDb3B5
'' SIG '' cmlnaHQgKGMpIDE5OTcgTWljcm9zb2Z0IENvcnAuMR4w
'' SIG '' HAYDVQQLExVNaWNyb3NvZnQgQ29ycG9yYXRpb24xITAf
'' SIG '' BgNVBAMTGE1pY3Jvc29mdCBSb290IEF1dGhvcml0eYIP
'' SIG '' AMEAizw8iBHRPvZj7N9AMBAGCSsGAQQBgjcVAQQDAgEA
'' SIG '' MB0GA1UdDgQWBBRv6E4/l7k0q0uGj7yc6qw7QUPG0DAZ
'' SIG '' BgkrBgEEAYI3FAIEDB4KAFMAdQBiAEMAQTALBgNVHQ8E
'' SIG '' BAMCAYYwDwYDVR0TAQH/BAUwAwEB/zANBgkqhkiG9w0B
'' SIG '' AQUFAAOCAQEAlE0RMcJ8ULsRjqFhBwEOjHBFje9zVL0/
'' SIG '' CQUt/7hRU4Uc7TmRt6NWC96Mtjsb0fusp8m3sVEhG28I
'' SIG '' aX5rA6IiRu1stG18IrhG04TzjQ++B4o2wet+6XBdRZ+S
'' SIG '' 0szO3Y7A4b8qzXzsya4y1Ye5y2PENtEYIb923juasxtz
'' SIG '' niGI2LS0ElSM9JzCZUqaKCacYIoPO8cTZXhIu8+tgzpP
'' SIG '' sGJY3jDp6Tkd44ny2jmB+RMhjGSAYwYElvKaAkMve0aI
'' SIG '' uv8C2WX5St7aA3STswVuDMyd3ChhfEjxF5wRITgCHIes
'' SIG '' BsWWMrjlQMZTPb2pid7oZjeN9CKWnMywd1RROtZyRLIj
'' SIG '' 9jGCBHcwggRzAgEBMIGHMHkxCzAJBgNVBAYTAlVTMRMw
'' SIG '' EQYDVQQIEwpXYXNoaW5ndG9uMRAwDgYDVQQHEwdSZWRt
'' SIG '' b25kMR4wHAYDVQQKExVNaWNyb3NvZnQgQ29ycG9yYXRp
'' SIG '' b24xIzAhBgNVBAMTGk1pY3Jvc29mdCBDb2RlIFNpZ25p
'' SIG '' bmcgUENBAgphD3hNAAAAAAADMAkGBSsOAwIaBQCggaIw
'' SIG '' GQYJKoZIhvcNAQkDMQwGCisGAQQBgjcCAQQwHAYKKwYB
'' SIG '' BAGCNwIBCzEOMAwGCisGAQQBgjcCARUwIwYJKoZIhvcN
'' SIG '' AQkEMRYEFH/8/6cpzCa/KIvvGNkJxBOn8qZUMEIGCisG
'' SIG '' AQQBgjcCAQwxNDAyoBiAFgBTAE0AVABQAFIAZQBnAC4A
'' SIG '' VgBiAHOhFoAUaHR0cDovL21pY3Jvc29mdC5jb20wDQYJ
'' SIG '' KoZIhvcNAQEBBQAEggEAlkDlp7NzW07FPTalzaZ9Dfvu
'' SIG '' +t1sBnR86zLfZeGe9vaEJ5XNluxkqckekJCk73y90H30
'' SIG '' +tqT0+EYVVO9V/B/ISS5Z5NakQM+OHvyO1+UJJpudnlK
'' SIG '' T+uz1fGB2X606wPib3DRPThfkOqB78Hbe8o3WrUL50Ee
'' SIG '' xecB6ARDlzyEdOU5oul4Y/nP2pK4F2zMZNHF2t3UYlRZ
'' SIG '' xjLzuT+Yk/UbJSKqjk/eTaSPcnMuLrtB6A4OKKdQRb8M
'' SIG '' t+n2nVnz4TXP3WQATHVFSDs+4nrDdKCuJxpDKVg3atZQ
'' SIG '' chmxBlt0g0HVASN72obBJz3cCCzxi0jb1zxoQOb0ebH4
'' SIG '' 2vH7SKL+e6GCAh8wggIbBgkqhkiG9w0BCQYxggIMMIIC
'' SIG '' CAIBATCBhzB5MQswCQYDVQQGEwJVUzETMBEGA1UECBMK
'' SIG '' V2FzaGluZ3RvbjEQMA4GA1UEBxMHUmVkbW9uZDEeMBwG
'' SIG '' A1UEChMVTWljcm9zb2Z0IENvcnBvcmF0aW9uMSMwIQYD
'' SIG '' VQQDExpNaWNyb3NvZnQgVGltZXN0YW1waW5nIFBDQQIK
'' SIG '' YUl87QAAAAAABTAHBgUrDgMCGqBdMBgGCSqGSIb3DQEJ
'' SIG '' AzELBgkqhkiG9w0BBwEwHAYJKoZIhvcNAQkFMQ8XDTA3
'' SIG '' MTEwODE2MTQ0OFowIwYJKoZIhvcNAQkEMRYEFBWjpKt1
'' SIG '' x7l7pws1y2efzyMfdDdXMA0GCSqGSIb3DQEBBQUABIIB
'' SIG '' AAwP9E87I8VE3lPLknflhuWiXzWZnmewuTLx7lbme88b
'' SIG '' mx54LMdYazIImKqIJ5ne+mIHgYuZiwIwFAIgXcbXabVX
'' SIG '' kNqh8p4WmnySsrGusNOu3vh9oSQh1xgjVxgfklYAxNFP
'' SIG '' wCLk9i82deH7ECWI5dYJMOV/D6pw3WPR38eeyx4lvXWB
'' SIG '' Aj4w1MnGJkLBqOWmrwhBoxbZnGA69e8ty48cr6NbPbv4
'' SIG '' U6u6JBVIbidc8+SXxlUVEtm+OvDlJ96Y2I0t5l8hGp9/
'' SIG '' mFDA6RNr3B9+yMrqUvRmznuSUvIGIesxQnE3C7eNjOig
'' SIG '' HSKfK5ODlGZpNCfN/TlQ0Tom7ujg4VkMIbE=
'' SIG '' End signature block
