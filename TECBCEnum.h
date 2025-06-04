//----------------------------------------------------------------------------
/// \file
/// Enumerations for TBarCode.
/// Contains all enumerations used in API-calls of TBarCode. 
/// \author TEC-IT Datenverarbeitung GmbH
/// \author Wagnerstr. 6, A-4400 Steyr, AUSTRIA/EUROPE
/// \author http://www.tec-it.com
/// \author Copyright&copy; by TEC-IT Datenverarbeitung GmbH
/// \date    1996-2007
/// \version 9.1
/// \note This product is supported. Please send an email to support@tec-it.com
//----------------------------------------------------------------------------

// ----------
// ATTENTION: Special treatment, when building TBarCode ActiveX (instead of TBarCode DLL)
// The type library of the TBarCode ActiveX contains this file.
// The MIDL tools automatically creates a header file 'TBarCode.h'. __TBarCode_h__ indicates
// that this file is used. If 'TBarCode.h' is used, then do not include this file.
#ifndef __TBarCode_h__    
// ----------


#ifndef __TECBCEnum_H
#define __TECBCEnum_H

//----------------------------------------------------------------------------
/// Help-String Macro (for ActiveX interface).
/// Expands to ["My String"] if compiling an .ODL file
/// \internal
//----------------------------------------------------------------------------
#ifdef TECIT_HELPSTRINGS
#  define   TECIT_HS(s) [helpstring(s)]
#else
#  undef    TECIT_HS
#  define   TECIT_HS(s)
#endif

/*//----------------------------------------------------------------------------
//
//  Standard print ratios
//
//  1B, 2B, 3B, 4B    .....   bar widths 
//  1S, 2S, 3S, 4S    .....   space widths 
//
//----------------------------------------------------------------------------*/
/* eBC_None,                Print ratios                                                    standard check digit                                */
                                                                                                            
/* eBC_Code11,              1:2.24:3.48:1:2.24          (1B:2B:3B:1S:2S)                    eCDNone                                             */
/* eBC_2OF5,                1:3:4.5:1:3                 (1B:2B:3B:1S:2S)                    eCDNone                                             */
/* eBC_2OF5IL,              1:3:1:3                     (1B:2B:1S:2S)                       eCDNone                                             */
/* eBC_2OF5IATA,            1:3:1                       (1B:2B:1S)                          eCDNone                                             */
/* eBC_2OF5M,               1:3:4.5:1:3                 (1B:2B:3B:1S:2S)                    eCDNone                                             */
/* eBC_2OF5DL,              1:3:1:3                     (1B:2B:1S:2S)                       eCDNone                                             */
/* eBC_2OF5IND,             1:3:1                       (1B:2B:1S)                          eCDNone                                             */
/* eBC_3OF9,                1:3:1:3                     (1B:2B:1S:2S)                       eCDNone                                             */
/* eBC_3OF9A,               1:3:1:3                     (1B:2B:1S:2S)                       eCDNone                                             */
/* eBC_EAN8,                1:2:3:4:1:2:3:4             (1B:2B:3B:4B:1S:2S:3S:4S)           eCDEAN8                                             */
/* eBC_EAN8P2,              1:2:3:4:1:2:3:4             (1B:2B:3B:4B:1S:2S:3S:4S)           eCDEAN8                                             */
/* eBC_EAN8P5,              1:2:3:4:1:2:3:4             (1B:2B:3B:4B:1S:2S:3S:4S)           eCDEAN8                                             */
/* eBC_EAN13,               1:2:3:4:1:2:3:4             (1B:2B:3B:4B:1S:2S:3S:4S)           eCDEAN13                                            */
/* eBC_EAN13P2,             1:2:3:4:1:2:3:4             (1B:2B:3B:4B:1S:2S:3S:4S)           eCDEAN13                                            */
/* eBC_EAN13P5,             1:2:3:4:1:2:3:4             (1B:2B:3B:4B:1S:2S:3S:4S)           eCDEAN13                                            */
/* eBC_EAN128,              1:2:3:4:1:2:3:4             (1B:2B:3B:4B:1S:2S:3S:4S)           eCDCode128                                          */
/* eBC_UPC12,               1:2:3:4:1:2:3:4             (1B:2B:3B:4B:1S:2S:3S:4S)           eCDUPCA                                             */
/* eBC_CodaBar2,            1:3:1:3                     (1B:2B:1S:2S)                       eCDNone                                             */
/* eBC_CodaBar18,           -------                                                         ----                                                */
/* eBC_Code128,             1:2:3:4:1:2:3:4             (1B:2B:3B:4B:1S:2S:3S:4S)           eCDCode128                                          */
/* eBC_Code128A,            1:2:3:4:1:2:3:4             (1B:2B:3B:4B:1S:2S:3S:4S)           eCDCode128                                          */
/* eBC_Code128B,            1:2:3:4:1:2:3:4             (1B:2B:3B:4B:1S:2S:3S:4S)           eCDCode128                                          */
/* eBC_Code128C,            1:2:3:4:1:2:3:4             (1B:2B:3B:4B:1S:2S:3S:4S)           eCDCode128                                          */
/* eBC_DPLeit,              1:3:1:3                     (1B:2B:1S:2S)                       eCDDPLeit                                           */
/* eBC_DPIdent,             1:3:1:3                     (1B:2B:1S:2S)                       eCDDPIdent                                          */
/* eBC_Code16K,             -------                                                         ----                                                */
/* eBC_49,                  -------                                                         ----                                                */
/* eBC_9OF3,                1:2:3:4:1:2:3:4             (1B:2B:3B:4B:1S:2S:3S:4S)           eCD2Mod47                                           */
/* eBC_UPC25,               -------                                                         ----                                                */
/* eBC_UPCD1,               -------                                                         ----                                                */
/* eBC_Flattermarken,       1:1                         (1B:1S)                             eCDNone                                             */
/* eBC_RSS14,               1:2:3:4:5:6:7:8:9:          (1B:2B:3B:4B:5B:6B:7B:8B:9B:        eCDNone                                             */
/*                          1:2:3:4:5:6:7:8:9            1S:2S:3S:4S:5S:6S:7S:8S:9S)                                                            */
/* eBC_RSSLtd,              1:2:3:4:5:6:7:8:9:          (1B:2B:3B:4B:5B:6B:7B:8B:9B:        eCDNone                                             */
/*                          1:2:3:4:5:6:7:8:9            1S:2S:3S:4S:5S:6S:7S:8S:9S)                                                            */
/* eBC_RSSExp,              -------                                                         ----                                                */
/* eBC_TelepenAlpha,        1:3:1:3                     (1B:2B:1S:2S)                       eCDNone                                             */
/* eBC_UCC128,              1:2:3:4:1:2:3:4             (1B:2B:3B:4B:1S:2S:3S:4S)           eCDCode128                                          */
/* eBC_UPCA,                1:2:3:4:1:2:3:4             (1B:2B:3B:4B:1S:2S:3S:4S)           eCDUPCA                                             */
/* eBC_UPCAP2,              1:2:3:4:1:2:3:4             (1B:2B:3B:4B:1S:2S:3S:4S)           eCDUPCA                                             */
/* eBC_UPCAP5,              1:2:3:4:1:2:3:4             (1B:2B:3B:4B:1S:2S:3S:4S)           eCDUPCA                                             */
/* eBC_UPCE,                1:2:3:4:1:2:3:4             (1B:2B:3B:4B:1S:2S:3S:4S)           eCDUPCE                                             */
/* eBC_UPCEP2,              1:2:3:4:1:2:3:4             (1B:2B:3B:4B:1S:2S:3S:4S)           eCDUPCE                                             */
/* eBC_UPCEP5,              1:2:3:4:1:2:3:4             (1B:2B:3B:4B:1S:2S:3S:4S)           eCDUPCE                                             */
/* eBC_USPSPostNet5,        1:1                         (1B:1S)                             eCDUSPSPostnet                                          */
/* eBC_USPSPostNet6,        1:1                         (1B:1S)                             eCDUSPSPostnet                                          */
/* eBC_USPSPostNet8,        1:1                         (1B:1S)                             eCDNone                                             */
/* eBC_USPSPostNet10,       1:1                         (1B:1S)                             eCDUSPSPostnet                                          */
/* eBC_USPSPostNet11,       1:1                         (1B:1S)                             eCDUSPSPostnet                                          */
/* eBC_USPSPostNet12,       1:1                         (1B:1S)                             eCDUSPSPostnet                                          */
/* eBC_Plessey,             1:2:1:2                     (1B:2B:1S:2S)                       eCDPlessey                                          */
/* eBC_MSI,                 1:2:1:2                     (1B:2B:1S:2S)                       eCDMSI1                                             */
/* eBC_SSCC18,              1:2:3:4:1:2:3:4             (1B:2B:3B:4B:1S:2S:3S:4S)           eCDMod10                                            */
/* eBC_FIM,                 -------                                                         ----                                                */
/* eBC_LOGMARS,             1:3:1:3                     (1B:2B:1S:2S)                       eCDNone                                             */
/* eBC_Pharma1,             1:3:2:4:2:3                 (1B:2B:1C:2C:1S:2S)                 eCDNone                                             */
/* eBC_PZN,                 1:2.5:1:2.5                 (1B:2B:1S:2S)                       eCDPZN                                              */
/* eBC_Pharma2,             1:1                         (1B:1S)                             eCDNone                                             */
/* eBC_GP,                  -------                                                         ----                                                */
/* eBC_PDF417,              1:2:3:4:5:6:7:8:            (1B:2B:3B:4B:5B:6B:7B:8B:                                                               
                            1:2:3:4:5:6                 1S:2S:3S:4S:5S:6S)                  eCDNone                                             */
/* eBC_PDF417Trunc,         1:2:3:4:5:6:7:8:            (1B:2B:3B:4B:5B:6B:7B:8B:                                                               
                            1:2:3:4:5:6                 1S:2S:3S:4S:5S:6S)                  eCDNone                                             */
/* eBC_MAXICODE,            -------                                                         ----                                                */
/* eBC_QRCode,              1:1                         (1B:1S)                             ----                                                */
/* eBC_Code128A,            1:2:3:4:1:2:3:4             (1B:2B:3B:4B:1S:2S:3S:4S)           eCDCode128                                          */
/* eBC_Code128B,            1:2:3:4:1:2:3:4             (1B:2B:3B:4B:1S:2S:3S:4S)           eCDCode128                                          */
/* eBC_Code128C,            1:2:3:4:1:2:3:4             (1B:2B:3B:4B:1S:2S:3S:4S)           eCDCode128                                          */
/* eBC_9OF3A,               1:2:3:4:1:2:3:4             (1B:2B:3B:4B:1S:2S:3S:4S)           eCD2Mod47                                           */
/* eBC_AusPostCustom,       1:1                         (1B:1S)                             eCDNone                                             */
/* eBC_AusPostCustom2,      1:1                         (1B:1S)                             eCDNone                                             */
/* eBC_AusPostCustom3,      1:1                         (1B:1S)                             eCDNone                                             */
/* eBC_AusPostReplyPaid,    1:1                         (1B:1S)                             eCDNone                                             */
/* eBC_AusPostRouting,      1:1                         (1B:1S)                             eCDNone                                             */
/* eBC_AusPostRedirect,     1:1                         (1B:1S)                             eCDNone                                             */
/* eBC_ISBN,                1:2:3:4:1:2:3:4             (1B:2B:3B:4B:1S:2S:3S:4S)           eCDEAN13                                            */
/* eBC_RM4SCC,              1:1                         (1B:1S)                             eCDNone                                             */
/* eBC_DataMatrix,          1:1                         (1B:1S)                             ----                                                */
/* eBC_EAN14,               1:2:3:4:1:2:3:4             (1B:2B:3B:4B:1S:2S:3S:4S)           eCDEAN14                                            */
/* eBC_CODABLOCK_E,         1:2:3:4:1:2:3:4             (1B:2B:3B:4B:1S:2S:3S:4S)           ----                                                */
/* eBC_CODABLOCK_F,         1:2:3:4:1:2:3:4             (1B:2B:3B:4B:1S:2S:3S:4S)           ----                                                */
/* eBC_NVE18,               1:2:3:4:1:2:3:4             (1B:2B:3B:4B:1S:2S:3S:4S)           eCDMod10                                            */
/* eBC_JapanesePostal       1:1                         (1B:1S)                             eCDNone                                             */
/* eBC_KoreanPostalAuth     1:3:4                       (1B:1S:2S)                          eCDMod10Kor                                         */
/* eBC_RSS14Trunc,          1:2:3:4:5:6:7:8:9:          (1B:2B:3B:4B:5B:6B:7B:8B:9B:        eCDNone                                             */
/*                          1:2:3:4:5:6:7:8:9            1S:2S:3S:4S:5S:6S:7S:8S:9S)                                                            */
/* eBC_RSS14Stacked,        1:2:3:4:5:6:7:8:9:          (1B:2B:3B:4B:5B:6B:7B:8B:9B:        eCDNone                                             */
/*                          1:2:3:4:5:6:7:8:9            1S:2S:3S:4S:5S:6S:7S:8S:9S)                                                            */
/* eBC_RSS14StackedOmni,    1:2:3:4:5:6:7:8:9:          (1B:2B:3B:4B:5B:6B:7B:8B:9B:        eCDNone                                             */
/*                          1:2:3:4:5:6:7:8:9            1S:2S:3S:4S:5S:6S:7S:8S:9S)                                                            */
/* eBC_RSSExpStacked,       1:2:3:4:5:6:7:8:9:          (1B:2B:3B:4B:5B:6B:7B:8B:9B:        eCDNone                                             */
/*                          1:2:3:4:5:6:7:8:9            1S:2S:3S:4S:5S:6S:7S:8S:9S)                                                            */
/* eBC_Planet12,            1:1                         (1B:1S)                             eCDMod10Pla                                         */
/* eBC_Planet14,            1:1                         (1B:1S)                             eCDMod10Pla                                         */
/* eBC_MicroPDF417,         1:2:3:4:5:6                 (1B:2B:3B:4B:5B:6B:                                                               
                            1:2:3:4:5:6                 1S:2S:3S:4S:5S:6S)                  eCDNone                                             */
/* eBC_USPSOneCode4CB,      1:1                         (1B:1S)                             eCDNone                                             */
/* eBC_PlesseyBidir,        1:2:3:1:2                   (1B:2B:3T:1S:2S)                    eCDPlessey                                          */
/* eBC_Telepen,             1:3:1:3                     (1B:2B:1S:2S)                       eCDNone                                             */
/* eBC_GS1_128,             1:2:3:4:1:2:3:4             (1B:2B:3B:4B:1S:2S:3S:4S)           eCDCode128                                          */
/* eBC_ITF14,               1:3:1:3                     (1B:2B:1S:2S)                       eCDMod10                                            */
/* eBC_KIX,                 1:1                         (1B:1S)                             eCDNone                                             */
/* eBC_BC412,               1:1                         (1B:1S)                             eCDNone                                             */
/* eBC_Aztec,               1:1                         (1B:1S)                             eCDNone                                             */
/* eBC_DAFT,                1:1                         (1B:1S)                             eCDNone                                             */
/* eBC_ItalianPostal2Of5,   1:3:1:3                     (1B:2B:1S:2S)                       eCDMod10ItlPst25                                    */
/* eBC_ItalianPostal3Of9,   -------                                                         ----                                                */
/* eBC_DPD,                 1:2:3:4:1:2:3:4             (1B:2B:3B:4B:1S:2S:3S:4S)           eCDCode128                                          */
/* eBC_MicroQRCode,         1:1                         (1B:1S)                             ----                                                */
/* eBC_HIBCLic128,          1:2:3:4:1:2:3:4             (1B:2B:3B:4B:1S:2S:3S:4S)           eCDMod43                                            */
/* eBC_HIBCLic39,           1:3:1:3                     (1B:2B:1S:2S)                       eCDMod43                                            */
/* eBC_HIBCPas128,          1:2:3:4:1:2:3:4             (1B:2B:3B:4B:1S:2S:3S:4S)           eCDMod43                                            */
/* eBC_HIBCPas39,           1:3:1:3                     (1B:2B:1S:2S)                       eCDMod43                                            */
/* eBC_HIBCLicDataMatrix,   1:1                         (1B:1S)                             eCDMod43                                            */
/* eBC_HIBCLicQRCode,       1:1                         (1B:1S)                             eCDMod43                                            */
/* eBC_HIBCLicPDF417,       1:2:3:4:5:6:7:8:            (1B:2B:3B:4B:5B:6B:7B:8B:                                                               
                            1:2:3:4:5:6                 1S:2S:3S:4S:5S:6S)                  eCDMod43                                            */
/* eBC_HIBCLicMPDF417,      1:2:3:4:5:6                 (1B:2B:3B:4B:5B:6B:                                                               
                            1:2:3:4:5:6                 1S:2S:3S:4S:5S:6S)                  eCDMod43                                            */
/* eBC_HIBCLicCODABLOCK_F,  1:2:3:4:1:2:3:4             (1B:2B:3B:4B:1S:2S:3S:4S)           eCDMod43                                            */
/* eBC_HIBCPasDataMatrix,   1:1                         (1B:1S)                             eCDMod43                                            */
/* eBC_HIBCPasQRCode,       1:1                         (1B:1S)                             eCDMod43                                            */
/* eBC_HIBCPasPDF417,       1:2:3:4:5:6:7:8:            (1B:2B:3B:4B:5B:6B:7B:8B:                                                               
                            1:2:3:4:5:6                 1S:2S:3S:4S:5S:6S)                  eCDMod43                                            */
/* eBC_HIBCPasMPDF417,      1:2:3:4:5:6                 (1B:2B:3B:4B:5B:6B:                                                               
                            1:2:3:4:5:6                 1S:2S:3S:4S:5S:6S)                  eCDMod43                                            */
/* eBC_HIBCPasCODABLOCK_F,  1:2:3:4:1:2:3:4             (1B:2B:3B:4B:1S:2S:3S:4S)           eCDMod43                                            */


//----------------------------------------------------------------------------
///  Supported Barcodes.
///  Enumerations for all supported barcode symbologies 
//----------------------------------------------------------------------------
typedef enum 
/// @cond INCLUDE_IN_DOXY
tag_BarCType            // This shall not appear in doxygen. Would create a confusing typedef in the doxygen doc.
/// @endcond 
{
  TECIT_HS("None")                            eBC_None        = 0,        ///< <b> No barcode type </b> \n Enumeration Value: 0
                                                                          ///< \n Nothing is drawn - use it when the bar code should be disabled.
                                                                          ///< \n
  TECIT_HS("Code 11")                         eBC_Code11      = 1,        ///< <b> Code 11 </b> \n Enumeration Value: 1 \n
                                                                          ///< - Codeable characters: ["0" - "9", "-"]
                                                                          ///< - Default check-digit method: None 
                                                                          ///< - Recommended check digit methods: #eCD1Code11 (one check-digits) or #eCD2Code11 (two check-digits)
                                                                          ///< \n\n
  TECIT_HS("Code 2OF5 Standard")              eBC_2OF5        = 2,        ///< <b> Code 2 of 5 </b>\n Enumeration Value: 2
                                                                          ///< \n The standard version - non interleaved; alias for Code 2 of 5 Matrix.
                                                                          ///< - Codeable characters: ["0" - "9"]
                                                                          ///< - Default check-digit method: None 
                                                                          ///< - Recommended check digit methods: #eCDMod10
                                                                          ///< \n\n
  TECIT_HS("Code 2OF5 Interleaved")           eBC_2OF5IL      = 3,        ///< <b> Interleaved 2 of 5 </b>\n Enumeration Value: 3
                                                                          ///< \n Interleaved version - encodes only an even number of digits, uses a leading "0" automatically (see BCSetAutoCorrect()).
                                                                          ///< - Codeable characters: ["0" - "9"]
                                                                          ///< - Default check-digit method: None 
                                                                          ///< - Recommended check digit methods: #eCDMod10
                                                                          ///< \n\n
  TECIT_HS("Code 2OF5 IATA")                  eBC_2OF5IATA    = 4,        ///< <b> Code 2 of 5 IATA </b>\n Enumeration Value: 4
                                                                          ///< \n The IATA version - non interleaved.
                                                                          ///< - Codeable characters: ["0" - "9"]
                                                                          ///< - Default check-digit method: None 
                                                                          ///< - Recommended check digit methods: #eCDMod10
                                                                          ///< \n\n
  TECIT_HS("Code 2OF5 Matrix")                eBC_2OF5M       = 5,        ///< <b> Code 2 of 5 Matrix </b> \n Enumeration Value: 5
                                                                          ///< \n Alias for Code 2 of 5 standard.
                                                                          ///< - Codeable characters: ["0" - "9"]
                                                                          ///< - Default check-digit method: None 
                                                                          ///< - Recommended check digit methods: #eCDMod10
                                                                          ///< \n\n
  TECIT_HS("Code 2OF5 DataLogic")             eBC_2OF5DL      = 6,        ///< <b> Code 2 of 5 Data Logic </b> \n Enumeration Value: 6  
                                                                          ///< \n Data Logic version of Code 2 of 5; not interleaved.
                                                                          ///< - Codeable characters: ["0" - "9"]
                                                                          ///< - Default check-digit method: None 
                                                                          ///< - Recommended check digit methods: #eCDMod10
                                                                          ///< \n\n 
  TECIT_HS("Code 2OF5 Industry")              eBC_2OF5IND     = 7,        ///< <b> Code 2 of 5 Industrial </b> \n Enumeration Value: 7
                                                                          ///< \n Industrial version of Code 2 of 5; not interleaved.
                                                                          ///< - Codeable characters: ["0" - "9"]
                                                                          ///< - Default check-digit method: None 
                                                                          ///< - Recommended check digit methods: #eCDMod10
                                                                          ///< \n\n
  TECIT_HS("Code 39")                         eBC_3OF9        = 8,        ///< <b> Code 3 of 9 (Code 39) </b> \n Enumeration Value: 8
                                                                          ///< \n In common use, start- and stop characters "*" (asterisk) are created automatically by TBarCode and must not be included in the input data
                                                                          ///< (start/stop characters are not displayed in the human readable text).
                                                                          ///< - Codeable characters: ["0"-"9", "A"-"Z", "-", ".", " ", "*", "$", "/", "+", "%"]
                                                                          ///< - Default check-digit method: None 
                                                                          ///< - Recommended check digit methods: #eCDMod43
                                                                          ///< \n\n
  TECIT_HS("Code 39 Full ASCII")              eBC_3OF9A       = 9,        ///< <b> Code 3 of 9 (Code 39) ASCII </b> \n Enumeration Value: 9
                                                                          ///< \n In common use, start- and stop characters "*" (asterisk) are created automatically by TBarCode and must not be included in the input data; they are not displayed in the human readable text.
                                                                          ///< - Codeable characters: All ASCII-characters from 0x00 to 0x7f (0 - 127)
                                                                          ///< - Default check-digit method: None
                                                                          ///< - Recommended check digit methods: #eCDMod43
                                                                          ///< \n\n 
  TECIT_HS("EAN8")                            eBC_EAN8        = 10,       ///< <b> EAN-8 </b> \n Enumeration Value: 10
                                                                          ///< \n In common use for retail applications and article numbering (EAN: European Article Numbering system), the check-digit is calculated automatically if not specified in the input data (that is when only 7 digits are used for creating the code).
                                                                          ///< - Encodes 7 digits and 1 check-digit
                                                                          ///< - Codeable characters: ["0" - "9"]
                                                                          ///< - Default check-digit method: #eCDEAN8 
                                                                          ///< - Recommended check digit methods: #eCDEAN8 (None for special applications)
                                                                          ///< 
                                                                          ///< \note Available as EAN.UCC Composite Symbology
                                                                          ///< \n\n 
  TECIT_HS("EAN8P2")                          eBC_EAN8P2      = 11,       ///< <b> EAN-8 with 2 digits add on </b> \n Enumeration Value: 11
                                                                          ///< \n In common use for retail applications and article numbering (EAN: European Article Numbering system), the check-digit is calculated automatically if not specified in the input data (that is when only 9 digits are used for creating the code).
                                                                          ///< - Encodes 7+2 digits and 1 check-digit
                                                                          ///< - Codeable characters: ["0" - "9"]
                                                                          ///< - Default check-digit method: #eCDEAN8 
                                                                          ///< - Recommended check digit methods: #eCDEAN8 (None for special applications)
                                                                          ///< \n\n
  TECIT_HS("EAN8P5")                          eBC_EAN8P5      = 12,       ///< <b> EAN-8 with 5 digits add on </b>\n Enumeration Value: 12
                                                                          ///< \n In common use for retail applications and article numbering (EAN: European Article Numbering system), the check-digit is calculated automatically if not specified in the input data (that is when only 11 digits are used for creating the code).
                                                                          ///< - Encodes 7+5 digits and 1 check-digit
                                                                          ///< - Codeable characters: ["0" - "9"]
                                                                          ///< - Default check-digit method: #eCDEAN8 
                                                                          ///< - Recommended check digit methods: #eCDEAN8 (None for special applications)
                                                                          ///< \n\n
  TECIT_HS("EAN13")                           eBC_EAN13       = 13,       ///< <b> EAN-13 </b> \n Enumeration Value: 13
                                                                          ///< \n In common use for retail applications and article numbering (EAN: European Article Numbering system), the check-digit is calculated automatically if not specified in the input data (that is when only 12 digits are used for creating the code). 
                                                                          ///< - Encodes 12 digits and 1 check-digit
                                                                          ///< - Codeable characters: ["0" - "9"]
                                                                          ///< - Default check-digit method: #eCDEAN13 
                                                                          ///< - Recommended check digit methods: #eCDEAN13 (None for special applications)
                                                                          ///<
                                                                          ///< \note Available as EAN.UCC Composite Symbology
                                                                          ///< \n\n
  TECIT_HS("EAN13P2")                         eBC_EAN13P2     = 14,       ///< <b> EAN-13 - with 2 digits add on </b> \n Enumeration Value: 14
                                                                          ///< \n In common use for retail applications and article numbering (EAN: European Article Numbering system), the check-digit is calculated automatically if not specified in the input data (that is when only 14 digits are used for creating the code).
                                                                          ///< - Encodes 12+2 digits and 1 check-digit
                                                                          ///< - Codeable characters: ["0" - "9"]
                                                                          ///< - Default check-digit method: #eCDEAN13 
                                                                          ///< - Recommended check digit methods: #eCDEAN13 (None for special applications)
                                                                          ///< \n\n
  TECIT_HS("EAN13P5")                         eBC_EAN13P5     = 15,       ///< <b> EAN-13 - with 5 digits add on </b> \n Enumeration Value: 15
                                                                          ///< \n In common use for retail applications and article numbering (EAN: European Article Numbering system), the check-digit is calculated automatically if not specified in the input data (that is when only 17 digits are used for creating the code). 
                                                                          ///< - Encodes 12+5 digits and 1 check-digit
                                                                          ///< - Codeable characters: ["0" - "9"]
                                                                          ///< - Default check-digit method: #eCDEAN13 
                                                                          ///< - Recommended check digit methods: #eCDEAN13 (None for special applications)
                                                                          ///< \n\n
  TECIT_HS("UCC/EAN-128")                     eBC_EAN128      = 16,       ///< <b> EAN-128 </b> \n Enumeration Value: 16
                                                                          ///< \n Is now called GS1-128 (See also GS1-128 )
                                                                          ///< - Codeable characters: All ASCII-characters from 0x00 to 0x7f (0 - 127)
                                                                          ///< - Default check-sum method: #eCDEAN128 (symbology internal checksum method)
                                                                          ///< - Recommended checksum calculation: #eCDEAN128, in addition #eCDMod10 or #eCDMod43 for special applications
                                                                          ///<
                                                                          ///< \note Available as EAN.UCC Composite Symbology
                                                                          ///< \n\n
  TECIT_HS("UPC12")                           eBC_UPC12       = 17,       ///< <b> UPC-12 Digits </b> \n Enumeration Value: 17
                                                                          ///< \n In common use for retail applications and article numbering (UPC: Universal Product Code), the check-digit is calculated automatically if not specified in the input data (that is when only 11 digits are used for creating the code) 
                                                                          ///< \n Check digit is calculated automatically if not specified in the input data (that is when only 11 digits are used for creating the code)
                                                                          ///< \n UPC-A and UPC-12 are identical.
                                                                          ///< - Encodes 11 digits and 1 check-digit
                                                                          ///< - Codeable characters: ["0" - "9"]
                                                                          ///< - Default check-digit method: #eCDUPCA
                                                                          ///< - Recommended check digit methods: #eCDUPCA, #eCDNone for special applications
                                                                          ///< \n\n
  TECIT_HS("Codabar 2 Widths")                eBC_CodaBar2    = 18,       ///< <b> Codabar (2 widths) </b> \n Enumeration Value: 18
                                                                          ///< \n Codabar using 2 different bar/space widths 
                                                                          ///< \n "A", "B", "C" or "D" are used as start/sop characters only.
                                                                          ///< - Codeable characters: ["0" - "9", "-", "$", ":", "/", ".", "+", "A", "B", "C", "D"]
                                                                          ///< - Default check-digit method: #eCDNone
                                                                          ///< - Recommended check digit methods: #eCDNone, #eCDMod16
                                                                          ///< \n\n
  TECIT_HS("Codabar 18 Widths")               eBC_CodaBar18   = 19,       ///< <b> Codabar (18 widths)</b> \n Enumeration Value: 19\n NOT SUPPORTED BY THE CURRENT VERSION.\n
                                                                          ///< \n
  TECIT_HS("Code128")                         eBC_Code128     = 20,       ///< <b> Code 128 </b> \n Enumeration Value: 20
                                                                          ///< \n In common use, beside this auto switching Code128 it is available in 3 different subsets (Code128A, Code128B, Code128C) 
                                                                          ///< \n Input data is analyzed and the best suited subset(s) will be used
                                                                          ///< \n Subset switching is also done automatically when necessary; the smallest possible symbol will be generated.
                                                                          ///< - The symbology internal check-digit (Mod 103) is calculated automatically
                                                                          ///< - Codeable characters: All ASCII-characters from 0x00 to 0x7f (0 - 127)
                                                                          ///< - Default check-sum method: #eCDCode128 (symbology internal checksum method)
                                                                          ///< - Recommended check digit methods: #eCDCode128, in addition #eCDMod10 or #eCDMod43 for special applications
                                                                          ///< \n\n
  TECIT_HS("DP Leitcode")                     eBC_DPLeit      = 21,       ///< <b> Deutsche Post Leitcode </b> \n Enumeration Value: 21
                                                                          ///< \n Used by Deutsche Post (is a variant of 2 of 5 interleaved), human readable text formatted according to specification.
                                                                          ///< - Encodes 13 digits and 1 symbology internal check-digit
                                                                          ///< - Codeable characters: ["0" - "9"]
                                                                          ///< - Default check-digit method: #eCDDPLeit
                                                                          ///< - Recommended check digit methods: #eCDDPLeit
                                                                          ///< \n\n
  TECIT_HS("DP Identcode")                    eBC_DPIdent     = 22,       ///< <b> Deutsche Post Identcode </b> \n Enumeration Value: 22
                                                                          ///< \n Used by Deutsche Post  (is a variant of 2 of 5 interleaved), human readable text formatted according to specification.
                                                                          ///< - Encodes 11 digits and 1 symbology internal check-digit
                                                                          ///< - Codeable characters: ["0" - "9"]
                                                                          ///< - Default check-digit method: #eCDDPIdent
                                                                          ///< - Recommended check digit methods: #eCDDPIdent
                                                                          ///< \n\n
  TECIT_HS("Code 16K")                        eBC_Code16K     = 23,       ///< <b> Code 16 K </b> \n Enumeration Value: 23\n NOT SUPPORTED BY THE CURRENT VERSION.\n
                                                                          ///< \n
  TECIT_HS("Code 49")                         eBC_49          = 24,       ///< <b> Code 49 </b> \n Enumeration Value: 24\n NOT SUPPORTED BY THE CURRENT VERSION.\n
                                                                          ///< \n
  TECIT_HS("Code 93")                         eBC_9OF3        = 25,       ///< <b> Code 93 </b> \n Enumeration Value: 25
                                                                          ///< \n In common use, offers higher data density than Code 39 (with same symbology character set).
                                                                          ///< - Codeable characters: ["0"-"9", "A"-"Z", "-", ".", Space, "$", "/", "+", "%"]
                                                                          ///< - Default check-sum calculation: #eCD2Mod47 (uses 2 checksum characters)
                                                                          ///< - Recommended checksum calculation: #eCD2Mod47
                                                                          ///< \n\n
  TECIT_HS("UPC25")                           eBC_UPC25       = 26,       ///< <b> UPC25 </b> \n Enumeration Value: 26\n NOT SUPPORTED BY THE CURRENT VERSION.\n
                                                                          ///< \n
  TECIT_HS("UPCD1")                           eBC_UPCD1       = 27,       ///< <b> UPCD1 </b> \n Enumeration Value: 27\n NOT SUPPORTED BY THE CURRENT VERSION.\n
                                                                          ///< \n
  TECIT_HS("Flattermarken")                   eBC_Flattermarken = 28,     ///< <b> Flattermarken </b> \n Enumeration Value: 28
                                                                          ///< - Codeable characters: ["0"-"9"]
                                                                          ///< - Default check-digit method: None
                                                                          ///< - Recommended check digit methods: None
                                                                          ///< \n\n
  TECIT_HS("GS1 DataBar (RSS-14)")            eBC_GS1DataBar  = 29,       ///< <b> GS1 DataBar (RSS-14, Reduced Space Symbology) </b> \n Enumeration Value: 29
                                                                          ///< \n Used to encode the GTIN (Global Trade Item Number) with Application identifier (AI) 01; 
                                                                          ///<   The GTIN consists of a packaging indicator (0-9) followed by a 12 digit number (taken from the EAN-13 article number system) followed by a check digit;
                                                                          ///<   The height of the symbol should be at least 33X to support omni-directional scanning (X = module width), no quiet zone is needed.
                                                                          ///< - Codeable characters: ["0"-"9"], the AI 01 is automatically encoded by TBarCode (must not be included in the input data!)
                                                                          ///< - The check digit is calculated automatically
                                                                          ///< - Default check-digit method: Check digit is part of the code
                                                                          ///< - Recommended check digit methods: None (is already part of the symbology)
                                                                          ///<
                                                                          ///< \note Available as EAN.UCC Composite Symbology
                                                                          ///< \n\n
  TECIT_HS("GS1 DataBar (RSS-14)")            eBC_RSS14       = 29,       ///< <b> GS1 DataBar (RSS-14, Reduced Space Symbology) </b> \n Enumeration Value: 29
                                                                          ///< \n Same as #eBC_GS1DataBar
                                                                          ///< \n\n
  TECIT_HS("GS1 DataBar Limited (RSS)")       eBC_GS1DataBarLtd = 30,     ///< <b> GS1 DataBar Limited (RSS Limited) </b> \n Enumeration Value: 30
                                                                          ///< \n Similar to RSS-14 but smaller in size and limited to packaging indicator 0 and 1 (first digit).
                                                                          ///< - No quiet zone is needed
                                                                          ///< - Encodes 13 digits and 1 check-digit
                                                                          ///< - Codeable characters: ["0"-"9"], 
                                                                          ///< - The check digit is calculated automatically
                                                                          ///< - Default check-digit method: None (Check digit is part of the code)
                                                                          ///< - Recommended check digit methods: None (is already part of the symbology)
                                                                          ///<
                                                                          ///< \note Available as EAN.UCC Composite Symbology
                                                                          ///< \n\n
  TECIT_HS("GS1 DataBar Limited (RSS)")       eBC_RSSLtd      = 30,       ///< <b> GS1 DataBar Limited (RSS Limited) </b> \n Enumeration Value: 30
                                                                          ///< \n Same as #eBC_GS1DataBarLtd
                                                                          ///< \n\n
  TECIT_HS("GS1 DataBar Expanded (RSS)")      eBC_GS1DataBarExp = 31,     ///< <b> GS1 DataBar Expanded (RSS Expanded) </b>\n Enumeration Value: 31
                                                                          ///< \n Reduced Space Symbology for encoding variable length of data with support for AI compaction; Omni-directional scanning is possible, also a stacked version is available (see #eBC_RSSExpStacked).
                                                                          ///< - No quiet zone is needed
                                                                          ///< - Encodes up to 74 numeric or 41 alphabetic characters
                                                                          ///< - Codeable characters: alphanumeric and special characters (ISO-646 table)
                                                                          ///< - The check digit is calculated automatically
                                                                          ///< - Default check-digit method: None (check digit is part of the code)
                                                                          ///< - Recommended check digit methods: None (check digit is part of the code)
                                                                          ///<
                                                                          ///< \note Available as EAN.UCC Composite Symbology
                                                                          ///< \n\n
  TECIT_HS("GS1 DataBar Expanded (RSS)")      eBC_RSSExp      = 31,       ///< <b> GS1 DataBar Expanded (RSS Expanded) </b>\n Enumeration Value: 31
                                                                          ///< \n Same as #eBC_GS1DataBarExp
                                                                          ///< \n\n
  TECIT_HS("Telepen Alpha")                   eBC_TelepenAlpha = 32,      ///< <b> Telepen Alpha </b> \n Enumeration Value: 32
                                                                          ///< \n Telepen Alpha is the alphanumeric variant of Telepen.
                                                                          ///< - Codeable characters: ASCII characters between 0-127
                                                                          ///< - Default check-digit method: None (check digit is part of the code)
                                                                          ///< - Recommended check digit methods: None (Check digit is part of the code)
                                                                          ///< \n\n
  TECIT_HS("UCC128")                          eBC_UCC128      = 33,       ///< <b>UCC-128 </b> \n Enumeration Value: 33
                                                                          ///< \n Same as GS1-128 or EAN-128 (refer to #eBC_EAN128).
                                                                          ///< \n\n
  TECIT_HS("UPCA")                            eBC_UPCA        = 34,       ///< <b> UPC A </b> \n Enumeration Value: 34
                                                                          ///< \n In common use for retail applications and article numbering (UPC: Universal Product Code); UPC-A and UPC-12 are identical;
                                                                          ///< \n The check digit is calculated automatically if not specified in the input data (that is when only 11 digits are used for creating the code).
                                                                          ///< - Encodes 11 digits and 1 check-digit
                                                                          ///< - Codeable characters: ["0" - "9"]
                                                                          ///< - Default check-digit method: #eCDUPCA
                                                                          ///< - Recommended check digit methods: #eCDUPCA (None for special applications)
                                                                          ///<
                                                                          ///< \note Available as EAN.UCC Composite Symbology
                                                                          ///< \n\n
  TECIT_HS("UPCAP2")                          eBC_UPCAP2      = 35,       ///< <b> UPC A - with 2 digit add on </b> \n Enumeration Value: 35
                                                                          ///< \n In common use for retail applications and article numbering (UPC Universal Product Code); The check digit is calculated automatically if not specified in the input data (that is when only 13 digits are used for creating the code).
                                                                          ///<
                                                                          ///< - Encodes 11+2 digits and 1 check-digit
                                                                          ///< - Codeable characters: ["0" - "9"]
                                                                          ///< - Default check-digit method: #eCDUPCA
                                                                          ///< - Recommended check digit methods: #eCDUPCA (None for special applications only)
                                                                          ///< \n\n 
  TECIT_HS("UPCAP5")                          eBC_UPCAP5      = 36,       ///< <b> UPC A - 5 digit add on </b> \n Enumeration Value: 36
                                                                          ///< \n In common use for retail applications and article numbering (UPC: Universal Product Code);
                                                                          ///< \n The check digit is calculated automatically if not specified in the input data (that is when only 16 digits are used for creating the code).
                                                                          ///< - Encodes 11+5 digits and 1 check-digit
                                                                          ///< - Codeable characters: ["0" - "9"]
                                                                          ///< - Default check-digit method: #eCDUPCA
                                                                          ///< - Recommended check digit methods: #eCDUPCA (None for special applications only)
                                                                          ///< \n\n 
  TECIT_HS("UPCE")                            eBC_UPCE        = 37,       ///< <b> UPC E </b> \n Enumeration Value: 37
                                                                          ///< \n In common use for retail applications and article numbering (UPC: Universal Product Code);
                                                                          ///< \n The check digit is calculated automatically if not specified in the input data (that is when only 7 digits are used for creating the code).
                                                                          ///< - Encodes 7 digits and 1 check-digit
                                                                          ///< - Codeable characters: ["0" - "9"]
                                                                          ///< - Default check-digit method: #eCDUPCE
                                                                          ///< - Recommended check digit methods: #eCDUPCE (None for special applications only)
                                                                          ///<
                                                                          ///< \note Available as EAN.UCC Composite Symbology
                                                                          ///< \n\n 
  TECIT_HS("UPCEP2")                          eBC_UPCEP2      = 38,       ///< <b> UPC E - with 2 digit add on </b> \n Enumeration Value: 38
                                                                          ///< \n In common use for retail applications and article numbering (UPC: Universal Product Code)
                                                                          ///< \n Check digit is calculated automatically if not specified in the input data (that is when only 9 digits are used for creating the code).
                                                                          ///< - Encodes 7+2 digits and 1 check-digit
                                                                          ///< - Codeable characters: ["0" - "9"]
                                                                          ///< - Default check-digit method: #eCDUPCE
                                                                          ///< - Recommended check digit methods: #eCDUPCE (None for special applications only)
                                                                          ///< \n\n 
  TECIT_HS("UPCEP5")                          eBC_UPCEP5      = 39,       ///< <b> UPC E - with 5 digit add on </b> \n Enumeration Value: 39
                                                                          ///< \n In common use for retail applications and article numbering (UPC: Universal Product Code)
                                                                          ///< \n Check digit is calculated automatically if not specified in the input data (that is when only 12 digits are used for creating the code).
                                                                          ///< - Encodes 7+5 digits and 1 check-digit
                                                                          ///< - Codeable characters: ["0" - "9"]
                                                                          ///< - Default check-digit method: #eCDUPCE
                                                                          ///< - Recommended check digit methods: #eCDUPCE (None for special applications)
                                                                          ///< \n\n 
  TECIT_HS("USPS PostNet5")                   eBC_USPSPostNet5    = 40,   ///< <b>USPS  PostNet ZIP (5 digits) </b> \n Enumeration Value: 40
                                                                          ///< \n USPS PostNet symbol for encoding the US ZIP Code (5 digits)
                                                                          ///< \n Check digit is always calculated automatically and cannot be specified in the input data.
                                                                          ///< - Encodes 5 digits and 1 check-digit
                                                                          ///< - Codeable characters: ["0" - "9"]
                                                                          ///< - Default check-digit method: #eCDUSPSPostnet
                                                                          ///< - Recommended check digit methods: #eCDUSPSPostnet
                                                                          ///< \n\n
  TECIT_HS("USPS PostNet6")                   eBC_USPSPostNet6    = 41,   ///< <b>USPS  PostNet ZIP (5 digits + check digit) </b> \n Enumeration Value: 41
                                                                          ///< \n USPS PostNet symbol for encoding the US ZIP Code (5 digits)
                                                                          ///< \n The required check digit is calculated automatically if length of input data equals 5; the user can also supply the 6th digit (no validation is performed).
                                                                          ///< - Encodes 5 digits and 1 check-digit
                                                                          ///< - Codeable characters: ["0" - "9"]
                                                                          ///< - Default check-digit method: #eCDUSPSPostnet (if 5 digits are specified for the input data), #eCDNone (if 6 digits are specified for the input data)
                                                                          ///< - Recommended check digit methods: #eCDUSPSPostnet
                                                                          ///< \n\n
  TECIT_HS("USPS PostNet9")                   eBC_USPSPostNet9    = 42,   ///< <b>USPS  PostNet ZIP+4 (5 digits + 4 digits) </b> \n Enumeration Value: 42
                                                                          ///< \n USPS PostNet symbol for encoding the ZIP+4 Code (5 digits ZIP code + 4 digits add-on)
                                                                          ///< \n Check digit is always calculated automatically and cannot be specified in the input data.
                                                                          ///< - Encodes 9 digits and 1 check-digit
                                                                          ///< - Codeable characters: ["0" - "9"]
                                                                          ///< - Default check-digit method: #eCDUSPSPostnet
                                                                          ///< - Recommended check digit methods: #eCDUSPSPostnet
                                                                          ///< \n\n
  TECIT_HS("USPS PostNet10")                  eBC_USPSPostNet10   = 43,   ///< <b>USPS  PostNet ZIP+4 (5 digits + 4 digits + CD)</b> \n Enumeration Value: 43
                                                                          ///< \n USPS PostNet symbol for encoding the ZIP+4 Code (5 digits ZIP code + 4 digits add-on)
                                                                          ///< \n The required check digit is calculated automatically if length of input data equals 9; the user can also supply the 10th digit (no validation is performed).
                                                                          ///< - Encodes 9 digits and 1 check-digit
                                                                          ///< - Codeable characters: ["0" - "9"]
                                                                          ///< - Default check-digit method: #eCDUSPSPostnet (if 9 digits are specified for the input data), #eCDNone (if 10 digits are specified for the input data)
                                                                          ///< - Recommended check digit methods: #eCDUSPSPostnet
                                                                          ///< \n\n
  TECIT_HS("USPS PostNet11")                  eBC_USPSPostNet11   = 44,   ///< <b>USPS  PostNet DPBC  (5 + 4 + 2 digits) </b> \n Enumeration Value: 44
                                                                          ///< \n USPS PostNet symbol for encoding the 11-digit Delivery Point Code (ZIP+4 followed by two DPBC numbers)
                                                                          ///< \n Check digit is always calculated automatically and cannot be specified in the input data.
                                                                          ///< - Encodes 11 digits and 1 check-digit
                                                                          ///< - Codeable characters: ["0" - "9"]
                                                                          ///< - Default check-digit method: #eCDUSPSPostnet
                                                                          ///< - Recommended check digit methods: #eCDUSPSPostnet
                                                                          ///< \n\n
  TECIT_HS("USPS PostNet12")                  eBC_USPSPostNet12 = 45,     ///< <b> USPS PostNet DPBC  (5 + 4 + 2 digits + CD) </b> \n Enumeration Value: 45
                                                                          ///< \n USPS PostNet symbol for encoding the 11-digit Delivery Point Code (ZIP+4 followed by two DPBC numbers)
                                                                          ///< \n The required check digit is calculated automatically if length of input data equals 11 - on demand the user can also supply the 12th digit (no validation is performed).
                                                                          ///< - Encodes 11 digits and 1 check-digit
                                                                          ///< - Codeable characters: ["0" - "9"]
                                                                          ///< - Default check-digit method: #eCDUSPSPostnet (if 11 digits are specified for the input data), #eCDNone (if 12 digits are specified for the input data)
                                                                          ///< - Recommended check digit methods: #eCDUSPSPostnet
                                                                          ///< \n\n
  TECIT_HS("Plessey")                         eBC_Plessey     = 46,       ///< <b> Plessey Code </b> \n Enumeration Value: 46
                                                                          ///< - Codeable characters: ["0"-"9", "A"-"Z"]
                                                                          ///< - Default check-digit method: #eCDPlessey (2 check characters are created)
                                                                          ///< - Recommended check digit methods: #eCDPlessey
                                                                          ///< \n\n
  TECIT_HS("MSI")                             eBC_MSI         = 47,       ///< <b> MSI Plessey Code </b> \n Enumeration Value: 47
                                                                          ///< \n MSI is available with 1 or 2 check digits (both are mod-10 based).
                                                                          ///< - Encodes 11 digits and 1 check-digit
                                                                          ///< - Codeable characters: ["0" - "9"]
                                                                          ///< - Default check-digit method: #eCDMSI1
                                                                          ///< - Recommended check digit methods: #eCDMSI1 (mod-10) or #eCDMSI2 (mod10 + mod10)
                                                                          ///< \n\n
  TECIT_HS("SSCC-18")                         eBC_SSCC18      = 48,       ///< <b> Serial Shipping Container Code 18 </b>  \n Enumeration Value: 48
                                                                          ///< \n Used to encode the 18 digit Serial Shipping Container Code based upon the UCC/EAN-128 symbology with Application Identifier (AI) prefix of "00"
                                                                          ///< \n The check digit is encoded automatically if 17 digits are used for input data
                                                                          ///< \n The leading AI "00" is encoded automatically by TBarCode (exclude it from input data!).
                                                                          ///< - Encodes 2 digits "00" + 17 digits and 1 check-digit
                                                                          ///< - Codeable characters: ["0" - "9"]
                                                                          ///< - Default check-digit method: #eCDMod10 (if 17 digits are specified for the input data), #eCDNone (if 18 digits are specified for the input data)
                                                                          ///< - Recommended check digit methods: #eCDMod10
                                                                          ///< \n\n
  TECIT_HS("FIM")                             eBC_FIM         = 49,       ///< <b> FIM (Facing Indication Mark) </b> \n Enumeration Value: 49\n NOT SUPPORTED BY THE CURRENT VERSION.\n
                                                                          ///< \n
  TECIT_HS("LOGMARS")                         eBC_LOGMARS     = 50,       ///< <b> LOGMARS </b> \n Enumeration Value: 50
                                                                          ///< \n Standardization of Code39 for military use  - please refer to Code 39 (#eBC_3OF9).
                                                                          ///< \n
  TECIT_HS("Pharmacode One-Track")            eBC_Pharma1     = 51,       ///< <b> Pharmacode (one-track) </b> \n Enumeration Value: 51
                                                                          ///< \n For medicine packing in pharmaceutically area (specification by Laetus?.
                                                                          ///< - Codeable characters: ["0" - "9"] or generic encoding
                                                                          ///< - Default check-digit method: #eCDNone
                                                                          ///< - Recommended check digit methods: #eCDNone
                                                                          ///< \n\n
  TECIT_HS("PZN")                             eBC_PZN         = 52,       ///< <b> PZN (Pharma Zentral Nummer Germany) </b>\n Enumeration Value: 52
                                                                          ///< \n PZN uses Code 39 as base symbology; It has a special check digit and the human readable text contains always the prefix "PZN-" (which is not encoded in the bar code data)
                                                                          ///< \n The required check digit is calculated automatically if 6 input digits are supplied.
                                                                          ///< - Encodes 6 digits and 1 check-digit
                                                                          ///< - Codeable characters: ["0" - "9"]
                                                                          ///< - Default check-digit method: #eCDPZN (if 6 digits specified for the input data), #eCDNone (if 7 digits specified for the input data)
                                                                          ///< - Recommended check digit methods: #eCDPZN
                                                                          ///< \n\n
  TECIT_HS("Pharmacode Two-Track")            eBC_Pharma2     = 53,       ///< <b> Pharmacode (two-track) </b>\n Enumeration Value: 53
                                                                          ///< \n For medicine packing in pharmaceutically area (specification by Laetus?; in opposition to #eBC_Pharma1 the information is contained in the vertical position of the bars.
                                                                          ///< - Codeable characters: ["0" - "9"]
                                                                          ///< - Default check-digit method: #eCDNone
                                                                          ///< - Recommended check digit methods: #eCDNone
                                                                          ///< \n\n
  TECIT_HS("General Parcel")                  eBC_GP          = 54,       ///< <b> General Parcel </b>\n Enumeration Value: 54\n NOT SUPPORTED BY THE CURRENT VERSION.\n
                                                                          ///< \n
  TECIT_HS("PDF417")                          eBC_PDF417      = 55,       ///< <b> PDF417 </b>\n Enumeration Value: 55
                                                                          ///< \n 2D symbology (multi-row) to encode large quantities of data
                                                                          ///< In default mode, input data is analyzed by TBarCode and best internal data compaction mode is switched (or shifted) automatically
                                                                          ///< \n Error correction and recognition is included in the code.
                                                                          ///< - Codeable characters: Alphanumeric (ASCII 0-255) and/or Bytes
                                                                          ///< - Default check-digit method: None
                                                                          ///< - Recommended check digit methods: None (Error correction and recognition depends on adjusted ECLevel)
                                                                          ///< \n\n
  TECIT_HS("PDF417 Truncated")                eBC_PDF417Trunc = 56,       ///< <b> PDF417 Truncated </b> \n Enumeration Value: 56
                                                                          ///< \n Similar to PDF417 but with synchronization bars only on the left side of the symbol
                                                                          ///< \n Refer to #eBC_PDF417 for details.
                                                                          ///< \n
  TECIT_HS("MaxiCode")                        eBC_MAXICODE    = 57,       ///< <b> MaxiCode </b>\n Enumeration Value: 57
                                                                          ///< \n MaxiCode is a two-dimensional code, created by UPS for high-speed sorting and tracking of unit loads and transport packages
                                                                          ///< \n Modes for including postal information (SCM) can be adjusted; Printing size is set to a norm value (can be changed with BCSetModWidth())
                                                                          ///< \n Error correction and recognition is included in the code.
                                                                          ///< - Codeable characters: alphanumeric and/or Bytes
                                                                          ///< - Default encoding mode: Mode-4 (standard symbol)
                                                                          ///< - Available modes for UPS: Mode 2 (SCM Numeric) and Mode 3 (SCM alphanumeric) - see BCSet_Maxi_Mode()
                                                                          ///< \n\n
  TECIT_HS("QR-Code")                         eBC_QRCode      = 58,       ///< <b> QR-Code </b>\n Enumeration Value: 58
                                                                          ///< \n 2D symbology to encode large quantities of data (implemented QR-Code model: 2)
                                                                          ///< \n The symbol version (size) adjusts automatically depending on input data or can be set to a specific value (BCSet_QR_Version()); Special industry formats are supported (BCSet_QR_Format())
                                                                          ///< \n Error correction and recognition is included in the code, support for Kanji characters can be enabled.
                                                                          ///< - Codeable characters: alphanumeric and/or Bytes, Kanji char set (Shift JIS X 0208)
                                                                          ///< - Default check-digit method: None
                                                                          ///< - Recommended check digit methods: None (Error correction and recognition depends on adjusted Error Correction Level)\n
                                                                          ///< \n
  TECIT_HS("Code128A")                        eBC_Code128A    = 59,       ///< <b> Code128 Subset A </b> \n Enumeration Value: 59
                                                                          ///< Same as #eBC_Code128 but symbology subset starts with A (instead of automatic determination).\n
                                                                          ///< \n
  TECIT_HS("Code128B")                        eBC_Code128B    = 60,       ///< <b> Code128 Subset B </b>\n Enumeration Value: 60
                                                                          ///< Same as #eBC_Code128 but symbology subset starts with B (instead of automatic determination).\n
                                                                          ///< \n
  TECIT_HS("Code128C")                        eBC_Code128C    = 61,       ///< <b> Code128 Subset C </b>\n Enumeration Value: 61
                                                                          ///< Same as #eBC_Code128 but symbology subset starts with C (instead of automatic determination).\n
                                                                          ///< \n
  TECIT_HS("Code 93 Full ASCII")              eBC_9OF3A       = 62,       ///< <b> Code 93  Ascii </b>\n Enumeration Value: 62
                                                                          ///< \n Extended version of Code 93 (#eBC_9OF3), which allows encoding of the full ASCII char set.
                                                                          ///< - Codeable characters: ASCII 0x00 - 0x7f (0-127)
                                                                          ///< - Default checksum method: #eCD2Mod47 (2 mod-47 checksum characters, which are always part of the generated code)
                                                                          ///< - Recommended checksum methods: #eCD2Mod47
                                                                          ///< \n\n
  TECIT_HS("Australian Post Custom")          eBC_AusPostCustom = 63,     ///< <b> Australian Post standard customer barcode </b>\n Enumeration Value: 63
                                                                          ///< \n Encodes the 8 digit Delivery Point Identifier (DPID) used by the Australian Post for mail sorting
                                                                          ///< \n Reed Solomon Error correction according to symbology specification is added automatically by TBarCode.
                                                                          ///< - Encodes 8 digits
                                                                          ///< - Codeable characters: ["0" - "9"]
                                                                          ///< - Default and recommended check-digit method: None
                                                                          ///< \n\n
  TECIT_HS("Australian Post Custom2")         eBC_AusPostCustom2 = 64,    ///< <b> Australian Post customer barcode 2 </b>\n Enumeration Value: 64
                                                                          ///< \n Encodes the 8 digit Delivery Point Identifier (DPID) followed by customer information (up to 5 characters)
                                                                          ///< \n Encodes 8 digits + 5 customer data characters + Reed Solomon Error Correction
                                                                          ///< \n Reed Solomon Error correction according to symbology specification is added automatically by TBarCode.
                                                                          ///< - Codeable characters DPID: ["0" - "9"]
                                                                          ///< - Codeable characters customer data: ["0" - "9", "A" - "Z", "a" - "z", Space, "#"] according to C Encoding Table in the Australian Post bar code specification (Table N is not supported in the current version of TBarCode)
                                                                          ///< - Default and recommended check-digit method: None
                                                                          ///< \n\n
  TECIT_HS("Australian Post Custom3")         eBC_AusPostCustom3 = 65,    ///< <b> Australian Post customer barcode 3 </b>\n Enumeration Value: 65
                                                                          ///< \n Encodes the 8 digit Delivery Point Identifier (DPID) followed by customer information (up to 10 characters)
                                                                          ///< \n Reed Solomon Error correction according to symbology specification is added automatically by TBarCode.
                                                                          ///< - Encodes 8 digits + 10 customer data characters
                                                                          ///< - Codeable characters DPID: ["0" - "9"]
                                                                          ///< - Codeable characters customer data: ["0" - "9", "A" - "Z", "a" - "z", Space, "#"] according to C Encoding Table in the Australian Post bar code specification (Table N is not supported in the current version of TBarCode)
                                                                          ///< - Default and recommended check-digit method: None
                                                                          ///< \n\n
  TECIT_HS("Australian Post Reply Paid")      eBC_AusPostReplyPaid = 66,  ///< <b> Australian Post Reply Paid barcode </b>\n Enumeration Value: 66
                                                                          ///< \n Encodes the 8 digit Sorting Code (DPID) used by the Australian Post, Format Control Code is set to 45 (Reply Paid Barcode)
                                                                          ///< \n Reed Solomon Error correction according to symbology specification is added automatically by TBarCode.
                                                                          ///< - Encodes 8 digits
                                                                          ///< - Codeable characters: ["0" - "9"]
                                                                          ///< - Default and recommended check-digit method: None
                                                                          ///< \n\n
  TECIT_HS("Australian Post Routing")         eBC_AusPostRouting = 67,   ///< <b> Australian Post Routing barcode </b>\n Enumeration Value: 67
                                                                          ///< \n Encodes the 8 digit Sorting Code (DPID) used by the Australian Post, Format Control Code is set to 87 (Routing Barcode)
                                                                          ///< \n Reed Solomon Error correction according to symbology specification is added automatically by TBarCode.
                                                                          ///< - Encodes 8 digits
                                                                          ///< - Codeable characters: ["0" - "9"]
                                                                          ///< - Default and recommended check-digit method: None
                                                                          ///< \n\n
  TECIT_HS("Australian Post Redirect")        eBC_AusPostRedirect = 68,   ///< <b> Australian Post Redirection barcode </b>\n Enumeration Value: 68
                                                                          ///< \n Encodes the 8 digit Sorting Code (DPID) used by the Australian Post, Format Control Code is set to 92 (Redirection Barcode)
                                                                          ///< \n Reed Solomon Error correction according to symbology specification is added automatically by TBarCode.
                                                                          ///< - Encodes 8 digits
                                                                          ///< - Codeable characters: ["0" - "9"]
                                                                          ///< - Default and recommended check-digit method: #eCDNone
                                                                          ///< \n\n
  TECIT_HS("ISBN")                            eBC_ISBN        = 69,       ///< <b> ISBN </b>\n Enumeration Value: 69
                                                                          ///< \n ISBN is used for encoding the ISBN number (used in the book industry) into a bar code for retail and wholesale applications
                                                                          ///< \n ISBN is based upon an EAN-13 P5 symbology (see #eBC_EAN13P5), the required check digit is calculated automatically if length of input data equals 17.
                                                                          ///< - Encodes 17 digits (12 + 5) and 1 check-digit
                                                                          ///< - Codeable characters: ["0" - "9"]
                                                                          ///< - Default check-digit method: #eCDEAN13 (if 17 digits are specified for the input data), #eCDNone (if 18 digits are specified for the input data)
                                                                          ///< - Recommended check digit methods: #eCDEAN13
                                                                          ///< \note Strip off the check digit from the ISBN number before you encode it into the symbol (otherwise you get a wrong bar code!)
                                                                          ///< \n\n
  TECIT_HS("Royal Mail 4 State (RM4SCC)")     eBC_RM4SCC      = 70,       ///< <b> Royal Mail 4 State customer code (RM4SCC)</b>\n Enumeration Value: 70
                                                                          ///< \n Used for automated mail sorting and addressing in the UK
                                                                          ///< \n Encodes a variable amount of characters followed by an internal calculated check-digit.
                                                                          ///< - Codeable characters: ["0" - "9", "A" - "Z"]
                                                                          ///< - Default check-digit method: #eCDRM4SCC (the required check character is added automatically by TBarCode)
                                                                          ///< - Recommended check digit methods: #eCDRM4SCC
                                                                          ///< \n\n
#ifndef TEC_DISABLE_DATAMATRIX
  TECIT_HS("Data Matrix")                     eBC_DataMatrix  = 71,       ///< <b> Data Matrix </b>\n Enumeration Value: 71
                                                                          ///< \n 2D matrix symbology developed to encode large quantities of data (especially on small objects), size adjusts automatically depending on input data (BCSet_DM_Size())
                                                                          ///< \n Symbology internal error correction (based upon ECC200) is added by TBarCode automatically
                                                                          ///< \n Input data is analyzed by TBarCode and the best suitable compaction mode is switched/shifted to during encoding.
                                                                          ///< - Encodes variable amount of data (up to 1556 Bytes or 2335 alpha numeric characters)
                                                                          ///< - Codeable characters: Alphanumeric and/or Bytes
                                                                          ///< - Default and recommended check-digit method: None (check digit and error correction is included in the code)
                                                                          ///< - Recommended check digit methods: None
                                                                          ///< \n\n
#endif // TEC_DISABLE_DATAMATRIX
  TECIT_HS("EAN14")                           eBC_EAN14       = 72,       ///< <b> EAN-14 </b>\n Enumeration Value: 72
                                                                          ///< \n Used to encode the GTIN (Global Trade Item Number) with Application Identifier (AI) 01
                                                                          ///< \n Within the EAN UCC System you can use 2 symbologies for encoding the GTIN: UCC/EAN-128 and ITF-14 (Code 2 of 5 interleaved with 14 digits)
                                                                          ///< \n Here we use EAN-128 with AI 01, the AI must not be part of the input data (it is prefixed automatically)
                                                                          ///< \n The check digit is calculated automatically if not specified in the input data (that is when only 13 digits are used).
                                                                          ///< - Codeable characters: see EAN128 (#eBC_EAN128)
                                                                          ///< - Default check-digit method: #eCDEAN14
                                                                          ///< - Recommended check digit methods: #eCDEAN14
                                                                          ///< \n\n
  TECIT_HS("CODABLOCK-E")                     eBC_CODABLOCK_E = 73,       ///< <b> CODABLOCK-E </b>\n Enumeration Value: 73\n NOT SUPPORTED IN THE CURRENT VERSION.\n
                                                                          ///< \n
  TECIT_HS("CODABLOCK-F")                     eBC_CODABLOCK_F = 74,       ///< <b> CODABLOCK-F </b>\n Enumeration Value: 74
                                                                          ///< \n Stacked version of Code128 symbology, each row is a single Code 128 symbol extended with row indicator information and additional check digits
                                                                          ///< \n The UCC/EAN/GS1 format indicator is supported (BCSet_CBF_Format()).
                                                                          ///< - Encodes variable amount of data
                                                                          ///< - Codeable characters: ASCII 0-127 + ISO 8859-1
                                                                          ///< - Default check-digit method: internal check digit method
                                                                          ///< - Recommended check digit methods: None (internal check digit method)
                                                                          ///< \n\n
  TECIT_HS("NVE-18")                          eBC_NVE18       = 75,       ///< <b> NVE-18 ("Nummer der Versandeinheit") </b>\n Enumeration Value: 75
                                                                          ///< \n Alias SSCC-18 - see #eBC_SSCC18.
                                                                          ///< \n
  TECIT_HS("Japanese Postal")                 eBC_JapanesePostal  = 76,   ///< <b> Japanese Postal customer code </b>\n Enumeration Value: 76
                                                                          ///< \n For customers of the Japanese Postal Service. You can encode the ZIP code followed by block and street number (Address-B data field) 
                                                                          ///< \n Address B data compaction can be enabled with Format Parameter "J" (BCSetFormat())); If format is set to "J", Japanese characters and also Chinese street numbers (encoded with Shift JIS char set) are converted to the Address-B data field by using the specified algorithm from the Japanese Postal Service.
                                                                          ///< - Encodes 7 digits (ZIP code) + additional data
                                                                          ///< - Codeable characters ZIP Code: ["0" - "9"]
                                                                          ///< - Codeable characters additional data: ["0" - "9", "A" - "Z", "-"] (Shift JIS characters are compacted if format "J" is set)
                                                                          ///< - Default check-digit method: None (the symbology internal check character is created automatically by TBarCode)
                                                                          ///< - Recommended check digit methods: None
                                                                          ///< \n\n
  TECIT_HS("Korean Postal Authority")         eBC_KoreanPostalAuth= 77,   ///< <b> Korean Postal Authority code </b>\n Enumeration Value: 77
                                                                          ///< \n Used by the Korean Postal Service for mail sorting
                                                                          ///< \n The symbology uses a special mod-10 based check digit, check digit calculation is enabled/disabled depending on the number of input characters.
                                                                          ///< - Encodes 6 digits + 1 check digit
                                                                          ///< - Codeable characters: ["0" - "9"]
                                                                          ///< - Default check-digit method: #eCDMod10Kor (if 6 digits are provided as for the input data), eCDNone (if 7 digits are provided)
                                                                          ///< - Recommended check digit methods: #eCDMod10Kor
                                                                          ///< \n\n
  TECIT_HS("GS1 DataBar Truncated (RSS)")     eBC_GS1DataBarTrunc = 78,   ///< <b> GS1 DataBar Truncated (RSS-14 Truncated) </b>\n Enumeration Value: 78
                                                                          ///< \n Similar to RSS-14 (#eBC_RSS14) but with reduced height (should be at least 13X; X = module width), omni-directional scanning may not be possible with truncated version, no quiet zone is needed for the RSS code family.
                                                                          ///< \note Available as EAN.UCC Composite Symbology
                                                                          ///< \n\n
  TECIT_HS("GS1 DataBar Truncated (RSS)")     eBC_RSS14Trunc   = 78,      ///< <b> GS1 DataBar Truncated (RSS-14 Truncated) </b>\n Enumeration Value: 78
                                                                          ///< \n Same as #eBC_GS1DataBarTrunc
                                                                          ///< \n\n
  TECIT_HS("GS1 DataBar Stacked (RSS)")       eBC_GS1DataBarStacked = 79, ///< <b> GS1 DataBar Stacked (RSS-14 Stacked) </b>\n Enumeration Value: 79
                                                                          ///< \n Similar to RSS-14 (#eBC_RSS14) but split into 2 rows to make the symbol smaller, used for pharmaceutical packaging.
                                                                          ///< \note Available as EAN.UCC Composite Symbology
                                                                          ///< \n\n
  TECIT_HS("GS1 DataBar Stacked (RSS)")       eBC_RSS14Stacked = 79,      ///< <b> GS1 DataBar Stacked (RSS-14 Stacked) </b>\n Enumeration Value: 79
                                                                          ///< \n Same as #eBC_GS1DataBarStacked
                                                                          ///< \n\n
  TECIT_HS("GS1 DataBar Stacked Omni (RSS)")  eBC_GS1DataBarStackedOmni = 80,  ///< <b> GS1 DataBar Stacked Omnidirectional (RSS-14 Stacked Omnidirectional)</b>\n Enumeration Value: 80
                                                                          ///< \n This version of RSS-14 Stacked (#eBC_RSS14Stacked) supports omni-directional scanning, the increased symbol height makes this possible.
                                                                          ///< \note Available as EAN.UCC Composite Symbology
                                                                          ///< \n\n
  TECIT_HS("GS1 DataBar Stacked Omni (RSS)")  eBC_RSS14StackedOmni = 80,  ///< <b> GS1 DataBar Stacked Omnidirectional (RSS-14 Stacked Omnidirectional)</b>\n Enumeration Value: 80
                                                                          ///< \n Same as #eBC_GS1DataBarStackedOmni
                                                                          ///< \n\n
  TECIT_HS("GS1 DataBar Expanded Stacked (RSS)") eBC_GS1DataBarExpStacked = 81,  ///< <b> GS1 DataBar Expanded Stacked (RSS Expanded Stacked) </b>\n Enumeration Value: 81
                                                                          ///< \n Stacked version of RSS Expanded (#eBC_RSSExp), the number of data segments per row can vary between 4 and 22 (can be set with BCSet_RSS_SegmPerRow() - default segmentation is 4).
                                                                          ///< \note Available as EAN.UCC Composite Symbology
                                                                          ///< \n\n
  TECIT_HS("GS1 DataBar Expanded Stacked (RSS)") eBC_RSSExpStacked = 81,  ///< <b> GS1 DataBar Expanded Stacked (RSS Expanded Stacked) </b>\n Enumeration Value: 81
                                                                          ///< \n Same as #eBC_GS1DataBarExpStacked
                                                                          ///< \n\n
  TECIT_HS("Planet 12 digit")                 eBC_Planet12     = 82,      ///< <b> Planet Code 12 (2 + 5 + 4 digits + 1 CD Mod10) </b>\n Enumeration Value: 82
                                                                          ///< \n Used by the USPS (US Postal Service) for tracking inbound and outbound letter mail
                                                                          ///< \n The required check digit is calculated automatically by TBarCode if length of input data equals 11.
                                                                          ///< - Encodes 11 digits and 1 check-digit
                                                                          ///< - Codeable characters: ["0" - "9"]
                                                                          ///< - Default check-digit method: #eCDMod10Pla (if 11 digits are specified for the input data), #eCDNone (if 12 digits are specified for the input data)
                                                                          ///< - Recommended check digit methods: #eCDMod10Pla
                                                                          ///< \n\n
  TECIT_HS("Planet 14 digit")                 eBC_Planet14     = 83,      ///< <b> Planet Code 14 (2 + 5 + 6 digits + 1 CD Mod10) </b>\n Enumeration Value: 83
                                                                          ///< \n Used by the USPS (US Postal Service) for tracking inbound and outbound letter mail
                                                                          ///< \n The required check digit is calculated automatically by TBarCode if length of input data equals 13.
                                                                          ///< - Encodes 13 digits and 1 check-digit
                                                                          ///< - Codeable characters: ["0" - "9"]
                                                                          ///< - Default check-digit method: #eCDMod10Pla (if 13 digits are specified for the input data), #eCDNone (if 14 digits are specified for the input data)
                                                                          ///< - Recommended check digit methods: #eCDMod10Pla
                                                                          ///< \n\n
  TECIT_HS("MicroPDF417")                     eBC_MicroPDF417  = 84,      ///< <b> MicroPDF417 </b>\n Enumeration Value: 84
                                                                          ///< \n 2D / multi-row symbology to encode large quantities of data; Micro PDF is based upon PDF417 (#eBC_PDF417) but with specific variants of rows and columns - called "version" (BCSet_MPDF417_Version())
                                                                          ///< In default mode, input data is analyzed by TBarCode and best internal data compaction mode is selected (and dynamically switched) automatically
                                                                          ///< \n Error correction and recognition is included in the code.
                                                                          ///< - Encodable characters: alphanumeric (ASCII 0-255) and/or Bytes
                                                                          ///< - Default check-digit method: None
                                                                          ///< - Recommended check digit methods: None (number of error correction codewords is adapted to symbol version according to specification)
                                                                          ///< \n\n
  TECIT_HS("USPS OneCode (4-CB)")             eBC_USPSOneCode4CB = 85,    ///< <b> USPS OneCode (4-State Customer Barcode)</b>\n Enumeration Value: 85                                                                          
                                                                          ///< \n Height modulated bar code used for automated mail sorting and addressing by USPS.
																		                                      ///< \n Encodes a 20, 25, 29 or 31 digit string: 20 digits Tracking Code followed by the Routing Code (= ZIP Code with 0, 5, 9, or 11 digits).
                                                                          ///< The second digit must be "0" - "4".
                                                                          ///< - Codeable characters: ["0" - "9"]
                                                                          ///< - Default check-digit method: #eCDNone (the symbology specific check digit is added automatically by TBarCode)
                                                                          ///< - Recommended check digit methods: #eCDNone
                                                                          ///< \n\n
  TECIT_HS("Plessey Bidirectional")           eBC_PlesseyBidir = 86,      ///< <b> Plessey Code with bidirectional reading support</b> \n Enumeration Value: 86
                                                                          ///< \n
                                                                          ///< - Codeable characters: ["0"-"9", "A"-"Z"]
                                                                          ///< - Default check-digit method: #eCDPlessey (2 check characters are created)
                                                                          ///< - Recommended check digit methods: #eCDPlessey
                                                                          ///< \n\n
  TECIT_HS("Telepen")                         eBC_Telepen = 87,           ///< <b> Telepen </b> \n Enumeration Value: 87
                                                                          ///< \n The numeric version - encodes only an even number of digits, uses a leading "0" automatically (see BCSetAutoCorrect()).
                                                                          ///< \n Also an alphanumeric version of Telepen exists - Telepen Alpha.
                                                                          ///< - Codeable characters: ["0" - "9"]
                                                                          ///< - Default check-digit method: None (check digit is part of the code)
                                                                          ///< - Recommended check digit methods: None (Check digit is part of the code)
                                                                          ///< \n\n
  TECIT_HS("GS1-128")                         eBC_GS1_128 = 88,           ///< <b> GS1-128 </b> \n Enumeration Value: 88
                                                                          ///< \n GS1-128 (former called EAN 128) is based upon the Code128, but with the FNC1 function character encoded at the 2nd position (after the start code); this allows scanners and data processing software to differentiate EAN-128 from other symbologies.
                                                                          ///< - The FNC1 at 2nd position is inserted automatically by TBarCode
                                                                          ///< - The symbology internal checksum (Mod 103) is calculated automatically
                                                                          ///< - Within the GS1 System you can use Application Identifiers to prefix encoded data
                                                                          ///< - Codeable characters: All ASCII-characters from 0x00 to 0x7f (0 - 127)
                                                                          ///< - Default check-sum method: #eCDEAN128 (symbology internal checksum method)
                                                                          ///< - Recommended checksum calculation: #eCDEAN128, in addition #eCDMod10 or #eCDMod43 for special applications
                                                                          ///<
  TECIT_HS("ITF-14")                          eBC_ITF14 = 89,             ///< <b> ITF-14 </b>\n Enumeration Value: 89
                                                                          ///< \n ITF-14 is based upon 2of5 Interleaved but limited to 14 digits and ends with a check digit (mod 10) by default.
                                                                          ///< - Codeable characters: ["0" - "9"]
                                                                          ///< - Default check-digit method: #eCDMod10 
                                                                          ///< - Recommended check digit methods: #eCDMod10
                                                                          ///< \n\n
  TECIT_HS("KIX")                             eBC_KIX = 90,               ///< <b> KIX </b>\n Enumeration Value: 90
                                                                          ///< \n Used for automated mail sorting and addressing in the Netherlands (by TNT)
                                                                          ///< \n Encodes a variable amount of characters followed by an internal calculated check-digit.
                                                                          ///< - Codeable characters: ["0" - "9", "A" - "Z"]
                                                                          ///< - Default check-digit method: None
                                                                          ///< - Recommended check digit methods: None
                                                                          ///< \n\n
  TECIT_HS("BC412")                           eBC_BC412 = 91,             ///< <b> BC412 </b>\n Enumeration Value: 91\n NOT SUPPORTED BY THE CURRENT VERSION.\n
                                                                          ///< - Codeable characters: ["0"-"9", "A"-"Z"]
                                                                          ///< - Check digit calculation is a fix ingredient of the code
                                                                          ///< \n\n
  TECIT_HS("Aztec Code")                      eBC_Aztec = 92,             ///< <b> Aztec Code </b>\n Enumeration Value: 92
                                                                          ///< \n 2D matrix symbology developed to encode large quantities of data (especially on small objects), size adjusts automatically depending on input data (BCSet_Aztec_Size())
                                                                          ///< \n Symbology internal error correction is added by TBarCode automatically
                                                                          ///< \n Input data is analyzed by TBarCode and the best suitable compaction mode is switched/shifted to during encoding.
                                                                          ///< - Encodes variable amount of data (up to 1914 Bytes or 3067 alpha numeric characters)
                                                                          ///< - Codeable characters: Alphanumeric and/or Bytes
                                                                          ///< - Default and recommended check-digit method: None (check digit and error correction is included in the code)
                                                                          ///< - Recommended check digit methods: None
                                                                          ///< \n\n
  TECIT_HS("DAFT Code")                       eBC_DAFT = 93,              ///< <b> DAFT Code </b>\n Enumeration Value: 93
                                                                          ///< \n A generic 4 state code which consists of following 4 characters
                                                                          ///< - D ... Descender (medium bar - from center part to lower bound)
                                                                          ///< - A ... Ascender (medium bar - from center part to upper bound)
                                                                          ///< - F ... Full (full length bar - from upper to lower bound)
                                                                          ///< - T ... Tracker (short bar - center part only)
                                                                          ///< \n\n
  TECIT_HS("Italian Postal 2 of 5")           eBC_ItalianPostal2Of5 = 94, ///< <b> Italian Postal 2 of 5 </b>\n Enumeration Value: 94
                                                                          ///< \n Italian Postal 2 of 5 is based upon 2of5 Interleaved but limited to 12 digits and ends with a check digit by default.
                                                                          ///< - Codeable characters: ["0" - "9"]
                                                                          ///< - Default check-digit method: #eCDMod10ItlPst25
                                                                          ///< - Recommended check digit methods: #eCDMod10ItlPst25
                                                                          ///< \n\n
  TECIT_HS("Italian Postal 3 of 9")           eBC_ItalianPostal3Of9 = 95, ///< <b> Italian Postal 3 of 9 </b>\n Enumeration Value: 95\n NOT SUPPORTED IN THE CURRENT VERSION.\n
                                                                          ///< \n\n
  TECIT_HS("DPD")                             eBC_DPD = 96,               ///< <b> DPD Code </b> \n Enumeration Value: 96
                                                                          ///< \n DPD Code is based upon Code 128 and is used in DPD labels. 
                                                                          ///< \n The code in the barcode differs slightly from the display text.
                                                                          ///< The barcode data has following format (is entered by the user/application):
                                                                          ///< IPPPPPPPTTTTTTTTTTTTTTSSSCCC
                                                                          ///< whereas the display text looks as follows (is calculated from the barcode data):
                                                                          ///< PPPPPPPTTTTTTTTTTTTTTSSSCCCD
                                                                          ///< with:
                                                                          ///< - I        ... identification tag (only used in barcode)
                                                                          ///< - PPPPPPP  ... Destination Post Code
                                                                          ///< - TTTTTTTTTTTTTT  ... Tracking Number
                                                                          ///< - SSS  ... Service Code
                                                                          ///< - CCC  ... Destination Country Code
                                                                          ///< - D  ... Check Digit (mod 36) (only used in display text)
                                                                          ///< \n\n
  TECIT_HS("Micro QR-Code")                   eBC_MicroQRCode = 97,       ///< <b> Micro QR-Code </b>\n Enumeration Value: 97
                                                                          ///< \n 2D symbology, based upon QR-Code (#eBC_QRCode), but adapted to encode only small quantities of data (less overhead, smaller symbols).
                                                                          ///< \n The symbol version (size) adjusts automatically depending on input data or can be set to a specific value (BCSet_MQR_Version())
                                                                          ///< \n Error correction and recognition is included in the code, support for Kanji characters can be enabled.
                                                                          ///< - Codeable characters: alphanumeric and/or Bytes, Kanji char set (Shift JIS X 0208)
                                                                          ///< - Default check-digit method: None
                                                                          ///< - Recommended check digit methods: None (Error correction and recognition depends on adjusted Error Correction Level)\n
                                                                          ///< \n\n

  TECIT_HS("HIBC LIC 128")                    eBC_HIBCLic128 = 98,        ///< <b> HIBC LIC 128 </b>\n Enumeration Value: 98
                                                                          ///< \n HIBC LIC 128 uses Code 128 as base symbology; It has a special check digit (modulo 43) and the human readable text is surrounded by asterisks '*' (which are not encoded in the bar code data)
                                                                          ///< \n The content of HIBC LIC 128 / HIBC LIC 39 is specified by the HIBC Supplier Labeling Standard. It consists of a Primary and a Secondary Data Structure,
                                                                          ///< which may be encoded together in one bar code or split into 2 single symbols.
                                                                          ///< \n The primary format looks as follows: 
                                                                          ///< +IIIIP*UL
                                                                          ///< with:
                                                                          ///< - +        ... HIBC Supplier Labeling Flag '+'
                                                                          ///< - I        ... Label Identification Code (LIC)
                                                                          ///< - P*       ... Labelers Product or Catalog Number (field length: 1-13)
                                                                          ///< - U        ... Unit of Measure ID
                                                                          ///< - L        ... Check Digit (mod 43) - also used as "Link Character" in Secondary Data Structure
                                                                          ///< \n
                                                                          ///< \n The secondary format is defined as:
                                                                          ///< +R*Q*D*B*LC
                                                                          ///< with:
                                                                          ///< - +        ... HIBC Supplier Labeling Flag '+'
                                                                          ///< - R*       ... Quantity/Date Reference Identifier (length: 1, 2, or 5)
                                                                          ///< - Q*       ... Quantity Field (length: 0, 1, or 6)
                                                                          ///< - D*       ... Date Field (length: 0, or 5-9)
                                                                          ///< - B*       ... Lot/Batch/serial Number Field (length: 0-13)
                                                                          ///< - L        ... Link Character (check digit of Primary Data Structure)
                                                                          ///< - C        ... Check Digit (mod 43)
                                                                          ///< \n
                                                                          ///< \n The combined format is defined as:
                                                                          ///< +IIIIP*U/R*Q*D*B*C
                                                                          ///< with the fields specified as above. A slash (/) is used as separator. The check digit of the Primary, 
                                                                          ///< the '+' and the link character of the Secondary Data Format are omitted.
                                                                          ///< \n
                                                                          ///< - Default check-digit method: #eCDMod43
                                                                          ///< - Recommended check digit methods: #eCDMod43
                                                                          ///< \n\n
  TECIT_HS("HIBC LIC 39")                     eBC_HIBCLic3OF9 = 99,       ///< <b> HIBC LIC 39 </b>\n Enumeration Value: 99
                                                                          ///< \n For a short format description see also #eBC_HIBCLic128. 
                                                                          ///< \n\n
  TECIT_HS("HIBC PAS 128")                    eBC_HIBCPas128 = 100,       ///< <b> HIBC LIC 128 </b>\n Enumeration Value: 100
                                                                          ///< \n HIBC PAS 128 uses Code 128 as base symbology; It has a special check digit (modulo 43) and the human readable text is surrounded by asterisks '*' (which are not encoded in the bar code data)
                                                                          ///< \n The content of HIBC PAS 128 / HIBC PAS 39 is specified by the HIBC Provider Applications Standard. It may consist of a Single or a Split Data Field Format. 
                                                                          ///< The split format may be encoded together in one bar code or split into 2 single symbols.
                                                                          ///< \n The Single Data Structure Format looks as follows: 
                                                                          ///< +/F*G*DDDDDC1
                                                                          ///< with:
                                                                          ///< - +/       ... HIBC Provider Applications Standard Flag
                                                                          ///< - F*       ... Where Flag (length: 1 or 3)
                                                                          ///< - G*       ... What Flag (length: 1 or 3)
                                                                          ///< - D        ... Application Data
                                                                          ///< - C1       ... Check Digit (mod 43) - equal to the "Link Character" of the second part.
                                                                          ///< \n
                                                                          ///< \n The First Part of the Split data Structure Format looks like: 
                                                                          ///< +/1F*G*DDDDC
                                                                          ///< is much the same as the Single Format but with "1" as prefix and one position for the application data (D) less.
                                                                          ///< ("1" indicates that this is the first data structure)
                                                                          ///< \n
                                                                          ///< \n The Second Part of the Split Data Structure Format is defined as: 
                                                                          ///< +/2DDDDC1C2
                                                                          ///< with:
                                                                          ///< - +/       ... HIBC Provider Applications Standard Flag
                                                                          ///< - 2        ... "2" indicates that this is the second data structure
                                                                          ///< - D        ... Remainder of the Application Data
                                                                          ///< - C1       ... Link Character (check digit of first part)
                                                                          ///< - C2       ... Check Digit (mod 43)
                                                                          ///< \n
                                                                          ///< \n The combined format is defined as:
                                                                          ///< +/F*G1*D1D1D1/G2*D2D2D2C
                                                                          ///< with:
                                                                          ///< - +/       ... HIBC Provider Applications Standard Flag
                                                                          ///< - F*       ... Where Flag (length: 1 or 3)
                                                                          ///< - G1*      ... What Flag for D1(length: 1 or 3)
                                                                          ///< - D1       ... First Application Data
                                                                          ///< - G2*      ... What Flag for D2(length: 1 or 3)
                                                                          ///< - D2       ... Second Application Data
                                                                          ///< - C        ... Check Digit (mod 43)
                                                                          ///< \n
                                                                          ///< - Default check-digit method: #eCDMod43
                                                                          ///< - Recommended check digit methods: #eCDMod43
                                                                          ///< \n\n
  TECIT_HS("HIBC PAS 39")                     eBC_HIBCPas3OF9 = 101,      ///< <b> HIBC LIC 39 </b>\n Enumeration Value: 101
                                                                          ///< \n HIBC PAS 39 uses Code 3 of 9 as base symbology; It has a special check digit (modulo 43) and the human readable text is surrounded by asterisks '*' (which are not encoded in the bar code data)
                                                                          ///< \n For a short format description see also #eBC_HIBCPas128.
                                                                          ///< \n\n
#ifndef TEC_DISABLE_DATAMATRIX
  TECIT_HS("HIBC LIC Data Matrix")            eBC_HIBCLicDataMatrix = 102,///< <b> HIBC LIC Data Matrix </b>\n Enumeration Value: 102
                                                                          ///< \n HIBC LIC Data Matrix uses Data Matrix as base symbology; It has a special check digit (modulo 43).
                                                                          ///< \n For a short format description see also #eBC_HIBCLic128 (Single and Combined Format, splitting is not allowed). 
                                                                          ///< \n\n
  TECIT_HS("HIBC PAS Data Matrix")            eBC_HIBCPasDataMatrix = 103,///< <b> HIBC PAS Data Matrix </b>\n Enumeration Value: 103
                                                                          ///< \n HIBC PAS Data Matrix uses Data Matrix as base symbology; It has a special check digit (modulo 43).
                                                                          ///< \n For a short format description see also #eBC_HIBCPas128 (Primary and Combined Format, splitting is not allowed).
#endif // TEC_DISABLE_DATAMATRIX
  TECIT_HS("HIBC LIC QR-Code")                eBC_HIBCLicQRCode = 104,    ///< <b> HIBC LIC QR-Code </b>\n Enumeration Value: 104
                                                                          ///< \n HIBC LIC QR-Code uses QR-Code as base symbology; It has a special check digit (modulo 43).
                                                                          ///< \n For a short format description see also #eBC_HIBCLic128 (Single and Combined Format, splitting is not allowed). 
                                                                          ///< \n\n
  TECIT_HS("HIBC PAS QR-Code")                eBC_HIBCPasQRCode = 105,    ///< <b> HIBC PAS QR-Code </b>\n Enumeration Value: 105
                                                                          ///< \n HIBC PAS QR-Code uses QR-Code as base symbology; It has a special check digit (modulo 43).
                                                                          ///< \n For a short format description see also #eBC_HIBCPas128 (Primary and Combined Format, splitting is not allowed).
  TECIT_HS("HIBC LIC PDF417")                 eBC_HIBCLicPDF417 = 106,    ///< <b> HIBC LIC PDF417 </b>\n Enumeration Value: 106
                                                                          ///< \n HIBC LIC PDF417 uses PDF417 as base symbology; It has a special check digit (modulo 43).
                                                                          ///< \n For a short format description see also #eBC_HIBCLic128 (Single and Combined Format, splitting is not allowed). 
                                                                          ///< \n\n
  TECIT_HS("HIBC PAS PDF417")                 eBC_HIBCPasPDF417 = 107,    ///< <b> HIBC PAS PDF417 </b>\n Enumeration Value: 107
                                                                          ///< \n HIBC PAS PDF417 uses PDF417 as base symbology; It has a special check digit (modulo 43).
                                                                          ///< \n For a short format description see also #eBC_HIBCPas128 (Primary and Combined Format, splitting is not allowed).
  TECIT_HS("HIBC LIC MicroPDF417")            eBC_HIBCLicMPDF417 = 108,   ///< <b> HIBC LIC MicroPDF417 </b>\n Enumeration Value: 108
                                                                          ///< \n HIBC LIC MicroPDF417 uses MicroPDF417 as base symbology; It has a special check digit (modulo 43).
                                                                          ///< \n For a short format description see also #eBC_HIBCLic128 (Single and Combined Format, splitting is not allowed). 
                                                                          ///< \n\n
  TECIT_HS("HIBC PAS MicroPDF417")            eBC_HIBCPasMPDF417 = 109,   ///< <b> HIBC PAS MicroPDF417 </b>\n Enumeration Value: 109
                                                                          ///< \n HIBC PAS MicroPDF417 uses MicroPDF417 as base symbology; It has a special check digit (modulo 43).
                                                                          ///< \n For a short format description see also #eBC_HIBCPas128 (Primary and Combined Format, splitting is not allowed).
  TECIT_HS("HIBC LIC CODABLOCK-F")        eBC_HIBCLicCODABLOCK_F = 110,   ///< <b> HIBC LIC CODABLOCK-F </b>\n Enumeration Value: 110
                                                                          ///< \n HIBC LIC CODABLOCK-F uses CODABLOCK-F as base symbology; It has a special check digit (modulo 43).
                                                                          ///< \n For a short format description see also #eBC_HIBCLic128 (Single and Combined Format, splitting is not allowed). 
                                                                          ///< \n\n
  TECIT_HS("HIBC PAS CODABLOCK-F")        eBC_HIBCPasCODABLOCK_F = 111,   ///< <b> HIBC PAS CODABLOCK-F </b>\n Enumeration Value: 111
                                                                          ///< \n HIBC PAS CODABLOCK-F uses CODABLOCK-F as base symbology; It has a special check digit (modulo 43).
                                                                          ///< \n For a short format description see also #eBC_HIBCPas128 (Primary and Combined Format, splitting is not allowed).
} e_BarCType;


//----------------------------------------------------------------------------
///  Supported check-digit methods.
///  Enumerations for all supported check-digit methods 
//----------------------------------------------------------------------------
typedef enum 
/// @cond INCLUDE_IN_DOXY
tag_CDMethod            // This shall not appear in doxygen. Would create a confusing typedef in the doxygen doc.
/// @endcond 
{
    TECIT_HS("None")                                eCDNone         = 0,     ///< =0: No check digit calculation is performed      
    TECIT_HS("Standard")                            eCDStandard     ,        ///< =1: Standard check digit of barcode type will be used
    TECIT_HS("Modulo 10")                           eCDMod10        ,        ///< =2: Modulo 10 (usually used with Interleaved 2of5)                                             
    TECIT_HS("Modulo 43")                           eCDMod43        ,        ///< =3: Modulo 43 (suggested for Code39 and Logmars, consist of 1 digit)                                             
    TECIT_HS("Modulo 47 (2 digits)")                eCD2Mod47       ,        ///< =4: Modulo 47 (2 digits)                                             
    TECIT_HS("DP Leitcode")                         eCDDPLeit       ,        ///< =5: Method for DP Leitcode                                             
    TECIT_HS("DP Identcode")                        eCDDPIdent      ,        ///< =6: Method for DP Identcode                                             
    TECIT_HS("Code11 (1 digit)")                    eCD1Code11      ,        ///< =7: Method for Code11 (1 digit)                                             
    TECIT_HS("Code11 (2 digits)")                   eCD2Code11      ,        ///< =8: Method for Code11 (2 digits)                                             
    TECIT_HS("USPS PostNet")                        eCDUSPSPostnet  ,        ///< =9: Method for USPS PostNet                                             
    TECIT_HS("MSI (1 digit)")                       eCDMSI1         ,        ///< =10: Method for MSI (Modulo 10, 1 digit)                                             
    TECIT_HS("MSI (2 digits)")                      eCDMSI2         ,        ///< =11: Method for MSI (Modulo 10, 2 digits)                                             
    TECIT_HS("Plessey")                             eCDPlessey      ,        ///< =12: Method for Plessey                                             
    TECIT_HS("EAN 8")                               eCDEAN8         ,        ///< =13: Method for EAN 8                                             
    TECIT_HS("EAN 13")                              eCDEAN13        ,        ///< =14: Method for EAN 13                                              
    TECIT_HS("UPC A")                               eCDUPCA         ,        ///< =15: Method for UPC A                                             
    TECIT_HS("UPC E")                               eCDUPCE         ,        ///< =16: Method for UPC E                                             
    TECIT_HS("EAN 128")                             eCDEAN128       ,        ///< =17: EAN 128 internal method (Modulo 103)                                             
    TECIT_HS("Code 128")                            eCDCode128      ,        ///< =18: Code 128 internal method (Modulo 103)                                             
    TECIT_HS("Royal Mail 4 State")                  eCDRM4SCC       ,        ///< =19: Method for Royal Mail 4 State                                             
    TECIT_HS("Mod-11 (PZN)")                        eCDPZN          ,        ///< =20: Mod 11 Method for PZN.
    TECIT_HS("Mod-11 (W=7)")                        eCDMod11W7      ,        ///< =21: Mod 11 (using weight 7)
    TECIT_HS("EAN 14")                              eCDEAN14        ,        ///< =22: Method for EAN 14
    TECIT_HS("Modulo 10 (Korean PA)")               eCDMod10Kor     ,        ///< =23: Method for Korean Postal Authority (Modulo 10 based)
    TECIT_HS("Modulo 10 (Planet)")                  eCDMod10Pla     ,        ///< =24: Method for Planet (Modulo 10 based)
    TECIT_HS("Modulo 10 (Italian Postal 2/5)")      eCDMod10ItlPst25,        ///< =25: Method for Italian Postal 2/5 (Modulo 10 based)
    TECIT_HS("Modulo 36 (DPD Barcode)")             eCDMod36        ,        ///< =26: Mod 36 (ISO/IES 7064) for DPD Barcode
    TECIT_HS("Modulo 16")                           eCDMod16        ,        ///< =27: Mod 16 for Codabar Barcode
} e_CDMethod;


//----------------------------------------------------------------------------
///  Supported barcode rotations.
///  Enumerations for all supported barcode rotations (counter-clockwise) 
//----------------------------------------------------------------------------
typedef enum 
/// @cond INCLUDE_IN_DOXY
tag_Degree            // This shall not appear in doxygen. Would create a confusing typedef in the doxygen doc.
/// @endcond 
{
    TECIT_HS("0 degrees")                           deg0            = 0,    ///< =0: No rotation
    TECIT_HS("90 degrees")                          deg90           = 1,    ///< =1: 90?rotated counter-clockwise
    TECIT_HS("180 degrees")                         deg180          = 2,    ///< =2: 180?rotated counter-clockwise (bottom-up)
    TECIT_HS("270 degrees")                         deg270          = 3     ///< =3: 270?rotated counter-clockwise
}
e_Degree;


//----------------------------------------------------------------------------
///  Supported measurement units.
///  Enumerations for all supported measurement units 
//----------------------------------------------------------------------------
typedef enum 
/// @cond INCLUDE_IN_DOXY
tag_MUnit            // This shall not appear in doxygen. Would create a confusing typedef in the doxygen doc.
/// @endcond 
{                                                   
    TECIT_HS("Default")                             eMUDefault      = 0,    ///< =0: Use units from the given device context (DC)
                                                                            ///<     In the context of quiet zone this value mostly means "no quiet zone")
    TECIT_HS("Pixel")                               eMUPixel        ,       ///< =1: Values are specified in Pixels (not used for bar width reduction)
    TECIT_HS("mm")                                  eMUMM           ,       ///< =2: Values are specified in Millimeter (mm) 
    TECIT_HS("Mils")                                eMUMils         ,       ///< =3: Values are specified in mils 
    TECIT_HS("Inch")                                eMUInch         ,       ///< =4: Values are specified in Inch
    TECIT_HS("Modules")                             eMUModules      ,       ///< =5: Only valid in the context of quiet zones:
                                                                            ///<     Quiet-Zone is specified in number of modules
    TECIT_HS("Percent")                             eMUPercent      ,       ///< =6: Only valid in the context of bar width reduction:
                                                                            ///<     The Bar Width reduction is specified in percent of the module width.
                                                                            ///<     The value is given in percent (0 ... 100).
} e_MUnit;

//----------------------------------------------------------------------------
///  Supported bearer bar types.
///  Enumerations for all supported bearer bar types
//----------------------------------------------------------------------------
typedef enum 
/// @cond INCLUDE_IN_DOXY
tag_BearerBar            // This shall not appear in doxygen. Would create a confusing typedef in the doxygen doc.
/// @endcond 
{       
  /// =0: No bearer bar.
  TECIT_HS("None (Default)") eBearerBar_None = 0, 

  /// =1: Bearer Bar is drawn on top and bottom of the bar code.
  TECIT_HS("Top and Bottom") eBearerBar_TopAndBottom = 1, 

  /// =2: Bearer Bar is drawn on all sides of the bar code.
  TECIT_HS("Rectangle") eBearerBar_Rectangle = 2,       

  /// =3: Bearer Bar is drawn on the upper side of the bar code.
  TECIT_HS("Top") eBearerBar_Top = 3,       

  /// =4: Bearer Bar is drawn on the bottom side of the bar code.
  TECIT_HS("Bottom") eBearerBar_Bottom = 4,
} e_BearerBar;

//----------------------------------------------------------------------------
///  Supported image output formats.
//----------------------------------------------------------------------------
typedef enum 
/// @cond INCLUDE_IN_DOXY
tag_ImageType            // This shall not appear in doxygen. Would create a confusing typedef in the doxygen doc.
/// @endcond 
{
    TECIT_HS("BMP")                                 eIMBmp          = 0,    ///< =0: BMP-Image
    TECIT_HS("EMF")                                 eIMEmf          ,       ///< =1: EMF-File (not supported in ConvertToStream and ConvertToStreamEx)
    TECIT_HS("EPS")                                 eIMEps          ,       ///< =2: EPS-Bitmap-Image (not supported in ConvertToStream and ConvertToStreamEx)
    TECIT_HS("GIF")                                 eIMGif          ,       ///< =3: GIF-Image 
    TECIT_HS("JPG")                                 eIMJpg          ,       ///< =4: JPG-Image
    TECIT_HS("PCX")                                 eIMPcx          ,       ///< =5: PCX-Image (not supported in ConvertToStream and ConvertToStreamEx)
    TECIT_HS("PNG")                                 eIMPng          ,       ///< =6: PNG-Image
    TECIT_HS("TIF")                                 eIMTif          ,       ///< =7: TIF-Image
    TECIT_HS("EPS-VECTOR")                          eIMEpsVector    ,       ///< =8: EPS-Vector-Image (not supported in ConvertToStream and ConvertToStreamEx)
} e_IMType;


//----------------------------------------------------------------------------
///  Supported alignments for the human readable text.
//----------------------------------------------------------------------------
typedef enum 
/// @cond INCLUDE_IN_DOXY
tag_Align            // This shall not appear in doxygen. Would create a confusing typedef in the doxygen doc.
/// @endcond 
{
    TECIT_HS("Default")                             eAlDefault      ,       ///< =0: Default alignment (centered)
    TECIT_HS("Left")                                eAlLeft         ,       ///< =1: Text is left-aligned 
    TECIT_HS("Right")                               eAlRight        ,       ///< =2: Text is right-aligned 
    TECIT_HS("Center")                              eAlCenter       ,       ///< =3: Text is centered
} e_BCAlign;


//----------------------------------------------------------------------------
//
//  License Enumerations
//
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
///  Available product variants for licensing (!!Attention: different values for different operation systems).
///  Enumeration Values for TBarCode for <b>Windows</b>:<ul><li>eLicProd1D = 44: (1D codes)<li>eLicProd2D = 45: (2D codes)</ul><br>
///  Enumeration Values for TBarCode for <b>Windows x64</b>:<ul><li>eLicProd1D = 48: (1D codes)<li>eLicProd2D = 49: (2D codes)</ul><br>
///  Enumeration Values for TBarCode for <b>Windows CE</b>:<ul><li>eLicProd1D = 46: (1D codes)<li>eLicProd2D = 47: (2D codes)</ul><br>
///  Enumeration Values for TBarCode for <b>Unix</b>:<ul><li>eLicProd1D = 114: (1D codes)<li>eLicProd2D = 115: (2D codes)</ul><br>
//----------------------------------------------------------------------------
#ifdef TEC_UNIX
  typedef enum 
  /// @cond INCLUDE_IN_DOXY
  tag_licProduct            // This shall not appear in doxygen. Would create a confusing typedef in the doxygen doc.
  /// @endcond 
  {
    TECIT_HS("Invalid product ID")                  eLicInvalid = -1,      ///< =-1: No valid product-id
    TECIT_HS("TBarCode 1D (standard)")              eLicProd1D = 114,      ///< : Generates linear barcodes only (values see above)
    TECIT_HS("TBarCode 2D (1D + 2D symbologies)")   eLicProd2D = 115,      ///< : Generates linear AND 2D codes (values see above)
  }
  e_licProduct;
#elif defined(TEC_WINCE)
  typedef enum 
  /// @cond INCLUDE_IN_DOXY
  tag_licProduct            // This shall not appear in doxygen. Would create a confusing typedef in the doxygen doc.
  /// @endcond 
  {
    TECIT_HS("Invalid product ID")                  eLicInvalid = -1,      ///< =-1: No valid product-id
    TECIT_HS("TBarCode 1D (standard)")              eLicProd1D = 46,       ///< : Generates linear barcodes only (values see above)
    TECIT_HS("TBarCode 2D (1D + 2D symbologies)")   eLicProd2D = 47,       ///< : Generates linear AND 2D codes (values see above)
  }
  e_licProduct;
#elif defined(TEC_WIN64)
  typedef enum 
  /// @cond INCLUDE_IN_DOXY
  tag_licProduct            // This shall not appear in doxygen. Would create a confusing typedef in the doxygen doc.
  /// @endcond 
  {
    TECIT_HS("Invalid product ID")                  eLicInvalid = -1,      ///< =-1: No valid product-id
    TECIT_HS("TBarCode 1D (standard)")              eLicProd1D = 48,       ///< : Generates linear barcodes only (values see above)
    TECIT_HS("TBarCode 2D (1D + 2D symbologies)")   eLicProd2D = 49,       ///< : Generates linear AND 2D codes (values see above)
  }
  e_licProduct;
#elif defined(TEC_SAP)
typedef enum 
/// @cond INCLUDE_IN_DOXY
tag_licProduct            // This shall not appear in doxygen. Would create a confusing typedef in the doxygen doc.
/// @endcond 
{
  TECIT_HS("Invalid product ID")                  eLicInvalid = -1,      ///< =-1: No valid product-id
  TECIT_HS("TBarCode 1D (standard)")              eLicProd1D = 59,       ///< : Generates linear barcodes only (values see above)
  TECIT_HS("TBarCode 2D (1D + 2D symbologies)")   eLicProd2D = 60,       ///< : Generates linear AND 2D codes (values see above)
}
e_licProduct;
#elif defined(TEC_WIN) && defined(TEC_TBCX)
  typedef enum 
  /// @cond INCLUDE_IN_DOXY
  tag_licProduct            // This shall not appear in doxygen. Would create a confusing typedef in the doxygen doc.
  /// @endcond 
  {
    TECIT_HS("Invalid product ID")                  eLicInvalid = -1,      ///< =-1: No valid product-id
    TECIT_HS("TBarCode 1D (standard)")              eLicProd1D = 51,       ///< : Generates linear barcodes only (values see above)
    TECIT_HS("TBarCode 2D (1D + 2D symbologies)")   eLicProd2D = 52,       ///< : Generates linear AND 2D codes (values see above)
  }
  e_licProduct;
#else /* WINDOWS */
  typedef enum 
  /// @cond INCLUDE_IN_DOXY
  tag_licProduct            // This shall not appear in doxygen. Would create a confusing typedef in the doxygen doc.
  /// @endcond 
  {
    TECIT_HS("Invalid product ID")                  eLicInvalid = -1,      ///< =-1: No valid product-id
    TECIT_HS("TBarCode 1D (standard)")              eLicProd1D = 44,       ///< : Generates linear barcodes only (values see above)
    TECIT_HS("TBarCode 2D (1D + 2D symbologies)")   eLicProd2D = 45,       ///< : Generates linear AND 2D codes (values see above)
  }
  e_licProduct;
#endif
  

//----------------------------------------------------------------------------
//
//  Product
//
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
///  Available license variants.
//----------------------------------------------------------------------------
typedef enum 
/// @cond INCLUDE_IN_DOXY
tag_licKind            // This shall not appear in doxygen. Would create a confusing typedef in the doxygen doc.
/// @endcond 
{
    TECIT_HS("Single (Einzellizenz)")               eLicKindSingle = 1,         ///< =1: Single license for exactly one computer
    TECIT_HS("Site (Firmenlizenz)")                 eLicKindSite = 2,           ///< =2: Site license for an arbitrary number of computers  within one site (or one facility) at one legal address
    TECIT_HS("Developer (Entwicklerlizenz)")        eLicKindDeveloper = 3,      ///< =3: Developer license for redistribution to 3rd party
    TECIT_HS("Web (Weblizenz)")                     eLicKindWeb = 3,            ///< =3: Web-server license
}
e_licKind;


//----------------------------------------------------------------------------
///  Available symbol-sizes for Data Matrix.
//----------------------------------------------------------------------------
#ifndef TEC_DISABLE_DATAMATRIX
typedef enum 
/// @cond INCLUDE_IN_DOXY
tagE_DMSizes            // This shall not appear in doxygen. Would create a confusing typedef in the doxygen doc.
/// @endcond 
{
    TECIT_HS("Default")                             eDMSz_Default,  ///< =0: Compute size of Data Matrix symbol automatically
    // Squares                                      
    TECIT_HS("10  x 10")                            eDMSz_10x10,    ///< =1: Fixed square symbol-size  10 x  10
    TECIT_HS("12  x 12")                            eDMSz_12x12,    ///< =2: Fixed square symbol-size  12 x  12
    TECIT_HS("14  x 14")                            eDMSz_14x14,    ///< =3: Fixed square symbol-size  14 x  14
    TECIT_HS("16  x 16")                            eDMSz_16x16,    ///< =4: Fixed square symbol-size  16 x  16
    TECIT_HS("18  x 18")                            eDMSz_18x18,    ///< =5: Fixed square symbol-size  18 x  18
    TECIT_HS("20  x 20")                            eDMSz_20x20,    ///< =6: Fixed square symbol-size  20 x  20
    TECIT_HS("22  x 22")                            eDMSz_22x22,    ///< =7: Fixed square symbol-size  22 x  22
    TECIT_HS("24  x 24")                            eDMSz_24x24,    ///< =8: Fixed square symbol-size  24 x  24
    TECIT_HS("26  x 26")                            eDMSz_26x26,    ///< =9: Fixed square symbol-size  26 x  26
    TECIT_HS("32  x 32")                            eDMSz_32x32,    ///< =10: Fixed square symbol-size  32 x  32
    TECIT_HS("36  x 36")                            eDMSz_36x36,    ///< =11: Fixed square symbol-size  36 x  36
    TECIT_HS("40  x 40")                            eDMSz_40x40,    ///< =12: Fixed square symbol-size  40 x  40
    TECIT_HS("44  x 44")                            eDMSz_44x44,    ///< =13: Fixed square symbol-size  44 x  44
    TECIT_HS("48  x 48")                            eDMSz_48x48,    ///< =14: Fixed square symbol-size  48 x  48
    TECIT_HS("52  x 52")                            eDMSz_52x52,    ///< =15: Fixed square symbol-size  52 x  52
    TECIT_HS("64  x 64")                            eDMSz_64x64,    ///< =16: Fixed square symbol-size  64 x  64
    TECIT_HS("72  x 72")                            eDMSz_72x72,    ///< =17: Fixed square symbol-size  72 x  72
    TECIT_HS("80  x 80")                            eDMSz_80x80,    ///< =18: Fixed square symbol-size  80 x  80
    TECIT_HS("88  x 88")                            eDMSz_88x88,    ///< =19: Fixed square symbol-size  88 x  88
    TECIT_HS("96  x 96")                            eDMSz_96x96,    ///< =20: Fixed square symbol-size  96 x  96
    TECIT_HS("104 x 104")                           eDMSz_104x104,  ///< =21: Fixed square symbol-size 104 x 104
    TECIT_HS("120 x 120")                           eDMSz_120x120,  ///< =22: Fixed square symbol-size 120 x 120
    TECIT_HS("132 x 132")                           eDMSz_132x132,  ///< =23: Fixed square symbol-size 132 x 132
    TECIT_HS("144 x 144")                           eDMSz_144x144,  ///< =24: Fixed square symbol-size 144 x 144
    // Rectangles                                   
    TECIT_HS("8   x 18")                            eDMSz_8x18,     ///< =25: Fixed rectangular symbol-size   8 x 18
    TECIT_HS("8   x 32")                            eDMSz_8x32,     ///< =26: Fixed rectangular symbol-size   8 x 32
    TECIT_HS("12  x 26")                            eDMSz_12x26,    ///< =27: Fixed rectangular symbol-size  12 x 26
    TECIT_HS("12  x 36")                            eDMSz_12x36,    ///< =28: Fixed rectangular symbol-size  12 x 36
    TECIT_HS("16  x 36")                            eDMSz_16x36,    ///< =29: Fixed rectangular symbol-size  16 x 36
    TECIT_HS("16  x 48")                            eDMSz_16x48,    ///< =30: Fixed rectangular symbol-size  16 x 48
} e_DMSizes;
#endif // TEC_DISABLE_DATAMATRIX


//----------------------------------------------------------------------------
///  Available encoding formats for Data Matrix.
//----------------------------------------------------------------------------
typedef enum 
/// @cond INCLUDE_IN_DOXY
tagE_DMFormat            // This shall not appear in doxygen. Would create a confusing typedef in the doxygen doc.
/// @endcond 
{
    TECIT_HS("Default")                             eDMPr_Default,  ///< =0: Default mode:        The standard format of Data Matrix without a special header.
    TECIT_HS("UCC/EAN/GS1")                         eDMPr_UCCEAN,   ///< =1: UCC/EAN/GS1 mode:    Special format defined by UCC and EAN/GS1 for encoding Application Identifiers. This format adds the function character FNC1 at 1st position in the symbol.
    TECIT_HS("Industry")                            eDMPr_Industry, ///< =2: Industry mode:       supports peculiar industry formats (adds FNC1 at 2nd position)
    TECIT_HS("Format 05")                           eDMPr_Macro05,  ///< =3: Macro 05 mode:       [)>Rs05Gs is encoded at the beginning of the code, RS + EOT is added as trailer
    TECIT_HS("Format 06")                           eDMPr_Macro06,  ///< =4: Macro 06 mode:       [)>Rs06Gs is encoded at the beginning of the code, RS + EOT is added as trailer
    TECIT_HS("Reader Programming")                  eDMPr_Reader,   ///< =5: Reader Programming:  Activate the Reader Programming Mode.
}  e_DMFormat;


//----------------------------------------------------------------------------
///  Available symbol-sizes for QR-Code.
//----------------------------------------------------------------------------
typedef enum 
/// @cond INCLUDE_IN_DOXY
tagE_QRVersion            // This shall not appear in doxygen. Would create a confusing typedef in the doxygen doc.
 /// @endcond 
{
    TECIT_HS("Default")                             eQRVers_Default,///< =0: Compute size of QR-Code symbol automatically
    TECIT_HS("(1) 21 x 21")                         eQRVers_1 ,     ///< =1: Fixed symbol-size 21 x 21 squares (Version 1)
    TECIT_HS("(2) 25 x 25")                         eQRVers_2 ,     ///< =2: Fixed symbol-size 25 x 25 squares (Version 2)
    TECIT_HS("(3) 29 x 29")                         eQRVers_3 ,     ///< =3: Fixed symbol-size 29 x 29 squares (Version 3)
    TECIT_HS("(4) 33 x 33")                         eQRVers_4 ,     ///< =4: Fixed symbol-size 33 x 33 squares (Version 4)
    TECIT_HS("(5) 37 x 37")                         eQRVers_5 ,     ///< =5: Fixed symbol-size 37 x 37 squares (Version 5)
    TECIT_HS("(6) 41 x 41")                         eQRVers_6 ,     ///< =6: Fixed symbol-size 41 x 41 squares (Version 6)
    TECIT_HS("(7) 45 x 45")                         eQRVers_7 ,     ///< =7: Fixed symbol-size 45 x 45 squares (Version 7)
    TECIT_HS("(8) 49 x 49")                         eQRVers_8 ,     ///< =8: Fixed symbol-size 49 x 49 squares (Version 8)
    TECIT_HS("(9) 53 x 53")                         eQRVers_9 ,     ///< =9: Fixed symbol-size 53 x 53 squares (Version 9)
    TECIT_HS("(10) 57 x 57")                        eQRVers_10,     ///< =10: Fixed symbol-size 57 x 57 squares (Version 10)
    TECIT_HS("(11) 61 x 61")                        eQRVers_11,     ///< =11: Fixed symbol-size 61 x 61 squares (Version 11)
    TECIT_HS("(12) 65 x 65")                        eQRVers_12,     ///< =12: Fixed symbol-size 65 x 65 squares (Version 12)
    TECIT_HS("(13) 69 x 69")                        eQRVers_13,     ///< =13: Fixed symbol-size 69 x 69 squares (Version 13)
    TECIT_HS("(14) 73 x 73")                        eQRVers_14,     ///< =14: Fixed symbol-size 73 x 73 squares (Version 14)
    TECIT_HS("(15) 77 x 77")                        eQRVers_15,     ///< =15: Fixed symbol-size 77 x 77 squares (Version 15)
    TECIT_HS("(16) 81 x 81")                        eQRVers_16,     ///< =16: Fixed symbol-size 81 x 81 squares (Version 16)
    TECIT_HS("(17) 85 x 85")                        eQRVers_17,     ///< =17: Fixed symbol-size 85 x 85 squares (Version 17)
    TECIT_HS("(18) 89 x 89")                        eQRVers_18,     ///< =18: Fixed symbol-size 89 x 89 squares (Version 18)
    TECIT_HS("(19) 93 x 93")                        eQRVers_19,     ///< =19: Fixed symbol-size 93 x 93 squares (Version 19)
    TECIT_HS("(20) 97 x 97")                        eQRVers_20,     ///< =20: Fixed symbol-size 97 x 97 squares (Version 20)
    TECIT_HS("(21) 101 x 101")                      eQRVers_21,     ///< =21: Fixed symbol-size 101 x 101 squares (Version 21)
    TECIT_HS("(22) 105 x 105")                      eQRVers_22,     ///< =22: Fixed symbol-size 105 x 105 squares (Version 22)
    TECIT_HS("(23) 109 x 109")                      eQRVers_23,     ///< =23: Fixed symbol-size 109 x 109 squares (Version 23)
    TECIT_HS("(24) 113 x 113")                      eQRVers_24,     ///< =24: Fixed symbol-size 113 x 113 squares (Version 24)
    TECIT_HS("(25) 117 x 117")                      eQRVers_25,     ///< =25: Fixed symbol-size 117 x 117 squares (Version 25)
    TECIT_HS("(26) 121 x 121")                      eQRVers_26,     ///< =26: Fixed symbol-size 121 x 121 squares (Version 26)
    TECIT_HS("(27) 125 x 125")                      eQRVers_27,     ///< =27: Fixed symbol-size 125 x 125 squares (Version 27)
    TECIT_HS("(28) 129 x 129")                      eQRVers_28,     ///< =28: Fixed symbol-size 129 x 129 squares (Version 28)
    TECIT_HS("(29) 133 x 133")                      eQRVers_29,     ///< =29: Fixed symbol-size 133 x 133 squares (Version 29)
    TECIT_HS("(30) 137 x 137")                      eQRVers_30,     ///< =30: Fixed symbol-size 137 x 137 squares (Version 30)
    TECIT_HS("(31) 141 x 141")                      eQRVers_31,     ///< =31: Fixed symbol-size 141 x 141 squares (Version 31)
    TECIT_HS("(32) 145 x 145")                      eQRVers_32,     ///< =32: Fixed symbol-size 145 x 145 squares (Version 32)
    TECIT_HS("(33) 149 x 149")                      eQRVers_33,     ///< =33: Fixed symbol-size 149 x 149 squares (Version 33)
    TECIT_HS("(34) 153 x 153")                      eQRVers_34,     ///< =34: Fixed symbol-size 153 x 153 squares (Version 34)
    TECIT_HS("(35) 157 x 157")                      eQRVers_35,     ///< =35: Fixed symbol-size 157 x 157 squares (Version 35)
    TECIT_HS("(36) 161 x 161")                      eQRVers_36,     ///< =36: Fixed symbol-size 161 x 161 squares (Version 36)
    TECIT_HS("(37) 165 x 165")                      eQRVers_37,     ///< =37: Fixed symbol-size 165 x 165 squares (Version 37)
    TECIT_HS("(38) 169 x 169")                      eQRVers_38,     ///< =38: Fixed symbol-size 169 x 169 squares (Version 38)
    TECIT_HS("(39) 173 x 173")                      eQRVers_39,     ///< =39: Fixed symbol-size 173 x 173 squares (Version 39)
    TECIT_HS("(40) 177 x 177")                      eQRVers_40,     ///< =40: Fixed symbol-size 177 x 177 squares (Version 40)
} e_QRVersion;

//----------------------------------------------------------------------------
///  Available encoding formats for QR-Code.
//----------------------------------------------------------------------------
typedef enum 
/// @cond INCLUDE_IN_DOXY
tagE_QRFormat            // This shall not appear in doxygen. Would create a confusing typedef in the doxygen doc.
/// @endcond 
{
    TECIT_HS("Default")                             eQRPr_Default,  ///< =0: The standard format of QR-Code without a special header
    TECIT_HS("UCC/EAN/GS1")                         eQRPr_UCCEAN,   ///< =1: Mode UCC/EAN/GS1: Special format defined by UCC and EAN/GS1. Used for encoding of so-called Application Identifiers (FNC1 is added at first position)
    TECIT_HS("Industry")                            eQRPr_Industry  ///< =2: Mode Industry: For special industry formats (FNC1 is inserted at second position). If you choose this value, you also have to fill out the field Application Indicator (2 digits or 1 letter). It determines to which industry format the input data (should) correspond(s)
}  e_QRFormat;

//----------------------------------------------------------------------------
///  Available error correction levels (ECC) for QR-Code.
//----------------------------------------------------------------------------
typedef enum 
/// @cond INCLUDE_IN_DOXY
tagE_QRECLevel            // This shall not appear in doxygen. Would create a confusing typedef in the doxygen doc.
/// @endcond 
{
    TECIT_HS("(L)ow")                             eQREC_Low,      ///< =0: Lowest level. Data recovery capacity is approximately up to 7%.
    TECIT_HS("(M)edium")                          eQREC_Medium,   ///< =1: Default EC-Level. Up to 15%
    TECIT_HS("(Q)uartil")                         eQREC_Quartil,  ///< =2: Up to 25%
    TECIT_HS("(H)igh")                            eQREC_High,     ///< =3: Highest level. Up to 30%
}  e_QRECLevel;

//----------------------------------------------------------------------------
///  Available mask patterns for QR-Code.
//----------------------------------------------------------------------------
typedef enum 
/// @cond INCLUDE_IN_DOXY
tagE_QRMask            // This shall not appear in doxygen. Would create a confusing typedef in the doxygen doc.
/// @endcond 
{
    TECIT_HS("Default")                           eQRMsk_Default = -1,    ///< =-1: Default: Mask is computed automatically (time consuming!)
    TECIT_HS("Mask 0")                            eQRMsk_0,               ///< =0: Use fixed mask 0 
    TECIT_HS("Mask 1")                            eQRMsk_1,               ///< =1: Use fixed mask 1 
    TECIT_HS("Mask 2")                            eQRMsk_2,               ///< =2: Use fixed mask 2 
    TECIT_HS("Mask 3")                            eQRMsk_3,               ///< =3: Use fixed mask 3 
    TECIT_HS("Mask 4")                            eQRMsk_4,               ///< =4: Use fixed mask 4 
    TECIT_HS("Mask 5")                            eQRMsk_5,               ///< =5: Use fixed mask 5 
    TECIT_HS("Mask 6")                            eQRMsk_6,               ///< =6: Use fixed mask 6 
    TECIT_HS("Mask 7")                            eQRMsk_7,               ///< =7: Use fixed mask 7 
}  e_QRMask;

//----------------------------------------------------------------------------
///  Available Multi Byte character compression (Kanji, Chinese) for QR-Code.
//----------------------------------------------------------------------------
typedef enum 
/// @cond INCLUDE_IN_DOXY
tagE_QRMBCompaction            // This shall not appear in doxygen. Would create a confusing typedef in the doxygen doc.
/// @endcond 
{
  TECIT_HS("Default MB compaction (Default)")     eQRMBCompactionDefault = -1,  ///< =-1: Default Multi Byte compaction: Choose the best compaction depending on code page
    TECIT_HS("No MB compaction")                  eQRMBCompactionNone,          ///< =0: Default: No Multi Byte character compression
    TECIT_HS("Kanji character compaction")        eQRMBCompactionKanji,         ///< =1: Use Kanji compaction (Multi Byte character set Shift JIS X 0208)
    TECIT_HS("Chinese character compaction")      eQRMBCompactionChinese,       ///< =2: Use Chinese compaction (Multi Byte character set GB2312)
}  e_QRMBCompaction;

//----------------------------------------------------------------------------
///  Available symbol-sizes for Micro QR-Code.
//----------------------------------------------------------------------------
typedef enum 
/// @cond INCLUDE_IN_DOXY
tagE_MQRVersion            // This shall not appear in doxygen. Would create a confusing typedef in the doxygen doc.
/// @endcond 
{
  TECIT_HS("Default")                             eMQRVers_Default,///< =0: Compute size of Micro QR-Code symbol automatically
  TECIT_HS("(M1) 11 x 11")                        eMQRVers_1 ,     ///< =1: Fixed symbol-size 11 x 11 squares (Version M1)
  TECIT_HS("(M2) 13 x 13")                        eMQRVers_2 ,     ///< =2: Fixed symbol-size 13 x 13 squares (Version M2)
  TECIT_HS("(M3) 15 x 15")                        eMQRVers_3 ,     ///< =3: Fixed symbol-size 15 x 15 squares (Version M3)
  TECIT_HS("(M4) 17 x 17")                        eMQRVers_4 ,     ///< =4: Fixed symbol-size 17 x 17 squares (Version M4)
} e_MQRVersion;

//----------------------------------------------------------------------------
///  Available mask patterns for Micro QR-Code.
//----------------------------------------------------------------------------
typedef enum 
/// @cond INCLUDE_IN_DOXY
tagE_MQRMask            // This shall not appear in doxygen. Would create a confusing typedef in the doxygen doc.
/// @endcond 
{
  TECIT_HS("Default")                             eMQRMsk_Default = -1,   ///< =-1: Default: Mask is computed automatically (time consuming!)
  TECIT_HS("Mask 0")                              eMQRMsk_0,              ///< =0: Use fixed mask 0 
  TECIT_HS("Mask 1")                              eMQRMsk_1,              ///< =1: Use fixed mask 1 
  TECIT_HS("Mask 2")                              eMQRMsk_2,              ///< =2: Use fixed mask 2 
  TECIT_HS("Mask 3")                              eMQRMsk_3,              ///< =3: Use fixed mask 3 
}  e_MQRMask;

//----------------------------------------------------------------------------
///  Available encoding formats for Codablock-F.
//----------------------------------------------------------------------------
typedef enum 
/// @cond INCLUDE_IN_DOXY
tagE_CBFFormat            // This shall not appear in doxygen. Would create a confusing typedef in the doxygen doc.
/// @endcond 
{
    TECIT_HS("Default")                             eCBFPr_Default,         ///< =0: Standard format
    TECIT_HS("UCC/EAN/GS1")                         eCBFPr_UCCEAN,          ///< =1: Special format defined by UCC and EAN/GS1 to be used in UCC/EAN/GS1 applications. Used for encoding of so-called Application Identifiers - a FNC1 is encoded at first position automatically.
}  e_CBFFormat;                                                             


//----------------------------------------------------------------------------
///  Available symbol sizes for MicroPDF.
//----------------------------------------------------------------------------
typedef enum 
/// @cond INCLUDE_IN_DOXY
tagE_MPDFVersions            // This shall not appear in doxygen. Would create a confusing typedef in the doxygen doc.
/// @endcond 
{
    TECIT_HS("Default (auto select)")               eMPDFVer_Default,       ///< =0: Compute size of MicroPDF symbol automatically
    TECIT_HS("1 x 11")                              eMPDFVer_1x11,          ///< =1: Fixed symbol-size columns x rows (1 x 11) 
    TECIT_HS("1 x 14")                              eMPDFVer_1x14,          ///< =2: Fixed symbol-size columns x rows (1 x 14)
    TECIT_HS("1 x 17")                              eMPDFVer_1x17,          ///< =3: Fixed symbol-size columns x rows (1 x 17)
    TECIT_HS("1 x 20")                              eMPDFVer_1x20,          ///< =4: Fixed symbol-size columns x rows (1 x 20)
    TECIT_HS("1 x 24")                              eMPDFVer_1x24,          ///< =5: Fixed symbol-size columns x rows (1 x 24)
    TECIT_HS("1 x 28")                              eMPDFVer_1x28,          ///< =6: Fixed symbol-size columns x rows (1 x 28)
            
    TECIT_HS("2 x 8")                               eMPDFVer_2x8,           ///< =7: Fixed symbol-size columns x rows (2 x 8)
    TECIT_HS("2 x 11")                              eMPDFVer_2x11,          ///< =8: Fixed symbol-size columns x rows (2 x 11)
    TECIT_HS("2 x 14")                              eMPDFVer_2x14,          ///< =9: Fixed symbol-size columns x rows (2 x 14)
    TECIT_HS("2 x 17")                              eMPDFVer_2x17,          ///< =10: Fixed symbol-size columns x rows (2 x 17)
    TECIT_HS("2 x 20")                              eMPDFVer_2x20,          ///< =11: Fixed symbol-size columns x rows (2 x 20)
    TECIT_HS("2 x 23")                              eMPDFVer_2x23,          ///< =12: Fixed symbol-size columns x rows (2 x 23)
    TECIT_HS("2 x 26")                              eMPDFVer_2x26,          ///< =13: Fixed symbol-size columns x rows (2 x 26)

    TECIT_HS("3 x 6")                               eMPDFVer_3x6,           ///< =14: Fixed symbol-size columns x rows (3 x 6)
    TECIT_HS("3 x 8")                               eMPDFVer_3x8,           ///< =15: Fixed symbol-size columns x rows (3 x 8)
    TECIT_HS("3 x 10")                              eMPDFVer_3x10,          ///< =16: Fixed symbol-size columns x rows (3 x 10)
    TECIT_HS("3 x 12")                              eMPDFVer_3x12,          ///< =17: Fixed symbol-size columns x rows (3 x 12)
    TECIT_HS("3 x 15")                              eMPDFVer_3x15,          ///< =18: Fixed symbol-size columns x rows (3 x 15)
    TECIT_HS("3 x 20")                              eMPDFVer_3x20,          ///< =19: Fixed symbol-size columns x rows (3 x 20)
    TECIT_HS("3 x 26")                              eMPDFVer_3x26,          ///< =20: Fixed symbol-size columns x rows (3 x 26)
    TECIT_HS("3 x 32")                              eMPDFVer_3x32,          ///< =21: Fixed symbol-size columns x rows (3 x 32)
    TECIT_HS("3 x 38")                              eMPDFVer_3x38,          ///< =22: Fixed symbol-size columns x rows (3 x 38)
    TECIT_HS("3 x 44")                              eMPDFVer_3x44,          ///< =23: Fixed symbol-size columns x rows (3 x 44)
            
    TECIT_HS("4 x 4")                               eMPDFVer_4x4,           ///< =24: Fixed symbol-size columns x rows (4 x 4)
    TECIT_HS("4 x 6")                               eMPDFVer_4x6,           ///< =25: Fixed symbol-size columns x rows (4 x 6)
    TECIT_HS("4 x 8")                               eMPDFVer_4x8,           ///< =26: Fixed symbol-size columns x rows (4 x 8)
    TECIT_HS("4 x 10")                              eMPDFVer_4x10,          ///< =27: Fixed symbol-size columns x rows (4 x 10)
    TECIT_HS("4 x 12")                              eMPDFVer_4x12,          ///< =28: Fixed symbol-size columns x rows (4 x 12)
    TECIT_HS("4 x 15")                              eMPDFVer_4x15,          ///< =29: Fixed symbol-size columns x rows (4 x 15)
    TECIT_HS("4 x 20")                              eMPDFVer_4x20,          ///< =30: Fixed symbol-size columns x rows (4 x 20)
    TECIT_HS("4 x 26")                              eMPDFVer_4x26,          ///< =31: Fixed symbol-size columns x rows (4 x 26)
    TECIT_HS("4 x 32")                              eMPDFVer_4x32,          ///< =32: Fixed symbol-size columns x rows (4 x 32)
    TECIT_HS("4 x 38")                              eMPDFVer_4x38,          ///< =33: Fixed symbol-size columns x rows (4 x 38)
    TECIT_HS("4 x 44")                              eMPDFVer_4x44,          ///< =34: Fixed symbol-size columns x rows (4 x 44)
} e_MPDFVers;


//----------------------------------------------------------------------------
///  Available encoding formats for Micro-PDF.
//----------------------------------------------------------------------------
typedef enum 
/// @cond INCLUDE_IN_DOXY
tagE_MPDFModes            // This shall not appear in doxygen. Would create a confusing typedef in the doxygen doc.
/// @endcond 
{
    TECIT_HS("Normal (Default)")                      eMPDFPr_Default,      ///< =0: Default encoding mode (choose best internal representation). Input data is analyzed and text, numeric or binary compaction mode will be used accordingly (to produce the smallest symbol).
    TECIT_HS("UCC/EAN/GS1-128 Emulation")             eMPDFPr_EAN128,       ///< =1: UCC/EAN/GS1-128 Emulation. Transmit ]C1 or ]L3, Use compaction for AI "01" + 14 digits
    TECIT_HS("Code 128 Emulation")                    eMPDFPr_C128Std,      ///< =2: Code128 Emulation. Transmit ]C2 or ]L4
    TECIT_HS("Code 128/FNC2 Emul.")                   eMPDFPr_C128FNC2,     ///< =3: Code128 FNC2 Emulation. Code-128 with FNC2 on first position will be emulated
    TECIT_HS("Linked UCC/EAN/GS1-128")                eMPDFPr_EAN128Lk,     ///< =4: Linked UCC/EAN/GS1-128 emulation. 
                                                                            ///< Transmit ]C1 or ]L3.
                                                                            ///< Indicates that the MicroPDF symbol is linked with a linear symbol (which may be required for a successful scan).
                                                                            ///< Using this mode, the following AIs in the given order can be encoded with better compaction:
                                                                            ///<
                                                                            ///< - date (AI 11, 13, 15 or 17) + lot number (AI 10) + other AIs (optional)
                                                                            ///< - date (AI 11, 13, 15 or 17) + serial number (AI 21) + other AIs (optional).
                                                                            ///< - date (AI 11, 13, 15 or 17) + other AIs (optional)
                                                                            ///< Note: This mode is not used with UCC.EAN Composite Symbology, which uses linked symbols, too
    TECIT_HS("05 Macro")                              eMPDFPr_05Macro,      ///< =5: 05 Macro. The preamble [ ( > RS 0 5 GS precedes the encoded data.
    TECIT_HS("06 Macro")                              eMPDFPr_06Macro,      ///< =6: 06 Macro. The preamble [ ( > RS 0 6 GS precedes the encoded data.
    TECIT_HS("CC-A Data Mode")                        eMPDFPr_CCA,          ///< =7: CC-A Data Mode. For special applications only: use Base-928 compaction, process input data as Byte array
    TECIT_HS("CC-B Prefix")                           eMPDFPr_CCB,          ///< =8: CC-B Data Mode. For special applications only: use binary compaction (Base-900), prefix symbol data with reserved symbology code word 
}  e_MPDFMode;

//----------------------------------------------------------------------------
///  Available encoding formats for PDF.
//----------------------------------------------------------------------------
typedef enum 
/// @cond INCLUDE_IN_DOXY
tagE_PDFModes            // This shall not appear in doxygen. Would create a confusing typedef in the doxygen doc.
/// @endcond 
{
    TECIT_HS("Normal (Default)")                      ePDFPr_Default,       ///< =0: Default encoding mode (choose best internal representation for non-binary data). Input data is analyzed and text, numeric or binary compaction mode will be used accordingly (to produce the smallest symbol).
    TECIT_HS("Binary Compaction")                     ePDFPr_Binary,        ///< =1: Binary Encoding (faster if binary data is to be encoded). Encoding will be in binary mode without further data analysis.
}  e_PDFMode;

//----------------------------------------------------------------------------
//
//  Aztec Code
//
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
///  Available symbol-sizes for Aztec Code.
//----------------------------------------------------------------------------
typedef enum 
/// @cond INCLUDE_IN_DOXY
tagE_AztecSizes            // This shall not appear in doxygen. Would create a confusing typedef in the doxygen doc.
/// @endcond 
{
    TECIT_HS("Default")                             eAztecSz_Default,  ///< =0: Compute size of Aztec symbol automatically
    TECIT_HS("15  x 15")                            eAztecSz_15x15,    ///< =1:  Fixed square symbol-size  15 x  15
    TECIT_HS("19  x 19")                            eAztecSz_19x19,    ///< =2:  Fixed square symbol-size  19 x  19
    TECIT_HS("23  x 23")                            eAztecSz_23x23,    ///< =3:  Fixed square symbol-size  23 x  23
    TECIT_HS("27  x 27")                            eAztecSz_27x27,    ///< =4:  Fixed square symbol-size  27 x  27
    TECIT_HS("31  x 31")                            eAztecSz_31x31,    ///< =5:  Fixed square symbol-size  31 x  31 (first full-range symbol)
    TECIT_HS("37  x 37")                            eAztecSz_37x37,    ///< =6:  Fixed square symbol-size  37 x  37
    TECIT_HS("41  x 41")                            eAztecSz_41x41,    ///< =7:  Fixed square symbol-size  41 x  41
    TECIT_HS("45  x 45")                            eAztecSz_45x45,    ///< =8:  Fixed square symbol-size  45 x  45
    TECIT_HS("49  x 49")                            eAztecSz_49x49,    ///< =9:  Fixed square symbol-size  49 x  49
    TECIT_HS("53  x 53")                            eAztecSz_53x53,    ///< =10: Fixed square symbol-size  53 x  53
    TECIT_HS("57  x 57")                            eAztecSz_57x57,    ///< =11: Fixed square symbol-size  57 x  57
    TECIT_HS("61  x 61")                            eAztecSz_61x61,    ///< =12: Fixed square symbol-size  61 x  61
    TECIT_HS("67  x 67")                            eAztecSz_67x67,    ///< =13: Fixed square symbol-size  67 x  67
    TECIT_HS("71  x 71")                            eAztecSz_71x71,    ///< =14: Fixed square symbol-size  71 x  71
    TECIT_HS("75  x 75")                            eAztecSz_75x75,    ///< =15: Fixed square symbol-size  75 x  75
    TECIT_HS("79  x 79")                            eAztecSz_79x79,    ///< =16: Fixed square symbol-size  79 x  79
    TECIT_HS("83  x 83")                            eAztecSz_83x83,    ///< =17: Fixed square symbol-size  83 x  83
    TECIT_HS("87  x 87")                            eAztecSz_87x87,    ///< =18: Fixed square symbol-size  87 x  87
    TECIT_HS("91  x 91")                            eAztecSz_91x91,    ///< =19: Fixed square symbol-size  91 x  91
    TECIT_HS("95  x 95")                            eAztecSz_95x95,    ///< =20: Fixed square symbol-size  95 x  95
    TECIT_HS("101 x 101")                           eAztecSz_101x101,  ///< =21: Fixed square symbol-size 101 x 101
    TECIT_HS("105 x 105")                           eAztecSz_105x105,  ///< =22: Fixed square symbol-size 105 x 105
    TECIT_HS("109 x 109")                           eAztecSz_109x109,  ///< =23: Fixed square symbol-size 109 x 109
    TECIT_HS("113 x 113")                           eAztecSz_113x113,  ///< =24: Fixed square symbol-size 113 x 113
    TECIT_HS("117 x 117")                           eAztecSz_117x117,  ///< =25: Fixed square symbol-size 117 x 117
    TECIT_HS("121 x 121")                           eAztecSz_121x121,  ///< =26: Fixed square symbol-size 121 x 121
    TECIT_HS("125 x 125")                           eAztecSz_125x125,  ///< =27: Fixed square symbol-size 125 x 125
    TECIT_HS("131 x 131")                           eAztecSz_131x131,  ///< =28: Fixed square symbol-size 131 x 131
    TECIT_HS("135 x 135")                           eAztecSz_135x135,  ///< =29: Fixed square symbol-size 135 x 135
    TECIT_HS("139 x 139")                           eAztecSz_139x139,  ///< =30: Fixed square symbol-size 139 x 139
    TECIT_HS("143 x 143")                           eAztecSz_143x143,  ///< =31: Fixed square symbol-size 143 x 143
    TECIT_HS("147 x 147")                           eAztecSz_147x147,  ///< =32: Fixed square symbol-size 147 x 147
    TECIT_HS("151 x 151")                           eAztecSz_151x151,  ///< =33: Fixed square symbol-size 151 x 151
    TECIT_HS("19  x 19 reader")                     eAztecSz_19x19_Rd, ///< =34: Fixed square symbol-size  19 x  19, used for reader initialization
    TECIT_HS("23  x 23 reader")                     eAztecSz_23x23_Rd, ///< =35: Fixed square symbol-size  23 x  23, used for reader initialization
    TECIT_HS("27  x 27 reader")                     eAztecSz_27x27_Rd, ///< =36: Fixed square symbol-size  27 x  27, used for reader initialization
    TECIT_HS("Aztec Rune")                          eAztecSz_Rune,     ///< =37: Fixed square symbol-size  11 x  11, Aztec Rune
} e_AztecSizes;

//----------------------------------------------------------------------------
///  Available encoding formats for Data Matrix.
//----------------------------------------------------------------------------
typedef enum 
/// @cond INCLUDE_IN_DOXY
tagE_AztecFormat            // This shall not appear in doxygen. Would create a confusing typedef in the doxygen doc.
/// @endcond 
{
    TECIT_HS("Default")                             eAztecFm_Default,  ///< =0: Default mode : The standard format of Data Matrix without a special header.
    TECIT_HS("UCC/EAN/GS1")                         eAztecFm_UCCEAN,   ///< =1: UCC/EAN/GS1 mode : Special format defined by UCC and EAN/GS1 for encoding Application Identifiers. This format adds the function character FNC1 at 1st position in the symbol.
    TECIT_HS("Industry")                            eAztecFm_Industry, ///< =2: Industry mode: supports peculiar industry formats (adds FNC1 at 2nd position)
}  e_AztecFormat;

//----------------------------------------------------------------------------
//
//  EAN.UCC Composite Symbology CC Type
//
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
///  Available Composite Component (CC) Types for EAN.UCC Composite Symbologies.
///  The composite component can be chosen automatically by TBarCode or adjusted by the user.
//----------------------------------------------------------------------------
typedef enum 
/// @cond INCLUDE_IN_DOXY
tagE_2DCompositeComponent            // This shall not appear in doxygen. Would create a confusing typedef in the doxygen doc.
/// @endcond 
{
  TECIT_HS("None")                                eCC_None,           ///< =0: Composite Symbologies are disabled.
  TECIT_HS("Auto Select")                         eCC_Auto,           ///< =1:Automatically choose CC-A, CC-B or CC-C Type depending on the length of the input data.
  TECIT_HS("CC-A")                                eCC_A,              ///< =2: Use composite component A (CC-A).
                                                                      ///< CC-A is a variant of the MicroPDF417 Symbol with a unique combination of row address patterns (RAP). It is the smallest variant of the 2-dimensional composite component. Up to 56 characters can be coded (also alphanumeric) with 3 to 12 rows and 4 columns.
  TECIT_HS("CC-B")                                eCC_B,              ///< =3: Use composite component B (CC-B).
                                                                      ///< CC-B is a subset of the MicroPDF417 Symbol, which is identified by the code word 920. CC-B will be chosen automatically when CC-A has not enough capacity (in Auto-mode). CC-B encodes up to 338 Characters (alphanumeric) in 3 to 12 rows and 2 to 4 columns.
  TECIT_HS("CC-C")                                eCC_C,              ///< =4: Use composite component C (CC-C).
                                                                      ///< The CC-C structure is a PDF417 Symbol, which is identified by the internal code word 920 (920 is the first code word after the symbol length indicator). The CC-C structure can be used as a 2 dimensional composite component of a UCC/EAN/GS1-128 Composite Symbols. It has the largest data capacity of EAN.UCC Composite Symbols because of its possibility to code of up to 2361 numbers. It can code numbers and alphanumeric characters with up to 2361 characters, which have 3 to 30 rows and up to 30 Data Error checking Code Columns.
}  e_CCType;


//----------------------------------------------------------------------------
///  Available options for trimming input data.
//----------------------------------------------------------------------------
typedef enum 
/// @cond INCLUDE_IN_DOXY
tagE_TrimSpaces            // This shall not appear in doxygen. Would create a confusing typedef in the doxygen doc.
/// @endcond 
{
  TECIT_HS("None")                                eTrim_None,         ///< =0: Do not trim input data
  TECIT_HS("Left")                                eTrim_Left,         ///< =1: Trim all spaces from left side of input data 
  TECIT_HS("Right")                               eTrim_Right,        ///< =2: Trim all spaces from right side of input data 
  TECIT_HS("All")                                 eTrim_All,          ///< =3: Trim all spaces from both sides of input data 
}
e_TrimSpaces;


//----------------------------------------------------------------------------
//
// enum BarSimm defaults
//
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//  Available options for BarSimm compatibility.
/// Not implemented now. Reserved for future versions.
//----------------------------------------------------------------------------
typedef enum 
/// @cond INCLUDE_IN_DOXY
tagE_DefaultSet            // This shall not appear in doxygen. Would create a confusing typedef in the doxygen doc.
/// @endcond 
{
    TECIT_HS("None")                                eBSDefault_None,
    TECIT_HS("Set1")                                eBSDefault_Set1,
    TECIT_HS("Set2")                                eBSDefault_Set2,
}
e_DefaultSet;


//----------------------------------------------------------------------------
///  Error codes returned by TBarCode.
//----------------------------------------------------------------------------
typedef enum 
/// @cond INCLUDE_IN_DOXY
tagE_ErrorCode            // This shall not appear in doxygen. Would create a confusing typedef in the doxygen doc.
/// @endcond 
{
    eErr_OK                       = 0x00000000L,                    ///<    No Error
    eErr_Invalid_Parameter        = 0x80070057L,                    ///<    Invalid parameter/unsupported value
    eErr_Invalid_Data             = 0x8007000DL,                    ///<    Wrong character
    eErr_Bad_Len                  = 0x80090004L,                    ///<    Wrong number of input characters
    eErr_Bad_Len_CC               = 0x80090005L,                    ///<    Invalid number of input characters in combination with Composite Component
    eErr_Too_Many_Characters      = 0x8007007AL,                    ///<    Input string too long
    eErr_Draw                     = 0x80040140L,                    ///<    Barcode does not fit into bounding rectangle
    eErr_Empty                    = 0x800710D2L,                    ///<    No input characters
    eErr_Not_Supported            = 0x80070032L,                    ///<    Composite Component not supported for selected bar code type
    eErr_Not_Implemented          = 0x80004001L,                    ///<    Not implemented (reserved for future use)
    eErr_Module_NotFound          = 0x8007007EL,                    ///<    External library is missing
    eErr_BCCreateNotCalled        = 0x8007065AL,                    ///<    BCCreate must be called before
    eErr_InvalidCodePage          = 0x8007203CL,                    ///<    Invalid code page or invalid characters
    eErr_BadFormat                = 0x8007000BL,                    ///<    Invalid data format. Please examine the specification
    eErr_WrongCheckDigit          = 0x8009700CL,                    ///<    Wrong check digit
}
e_ErrorCode;


/// Defines the supported color modes.
typedef enum 
/// @cond INCLUDE_IN_DOXY
tagE_ColorMode            // This shall not appear in doxygen. Would create a confusing typedef in the doxygen doc.
/// @endcond 
{
  enColorModeRgb,         ///< RGB color mode
  enColorModeGrayscale,   ///< Grayscale color mode
  enColorModeCmyk         ///< CMYK color mode
}
e_ColorMode;


/// Defines the supported color modes.
typedef enum 
/// @cond INCLUDE_IN_DOXY
tagE_PCLMode            // This shall not appear in doxygen. Would create a confusing typedef in the doxygen doc.
/// @endcond 
{
  enPCL5,             ///< PCL5 with HPGL/2
  enPCL5NoHPGL,       ///< PCL5 without HPGL/2
}
e_PCLMode;


//----------------------------------------------------------------------------
///  Type of barcode decoder (necessary for auto-computation of minimal module width).
//----------------------------------------------------------------------------
typedef enum 
/// @cond INCLUDE_IN_DOXY
tagE_Decoder            // This shall not appear in doxygen. Would create a confusing typedef in the doxygen doc.
/// @endcond 
{
  /// Barcode decoder is unknown or barcode may be scanned with hardware and software decoders.
	TECIT_HS("Barcode decoder is unknown or barcode may be scanned with hardware and software decoders.")  eDecoder_All = 0,
  /// Output is optimized for hardware barcode scanner.
  TECIT_HS("Hardware barcode scanner")	eDecoder_Hardware,
  /// Output is optimized for Software barcode scanner.
	TECIT_HS("Software barcode decoder")	eDecoder_Software,
  /// Output is optimized for TEC-IT's barcode scanning solution TBarCode InForm. 
  TECIT_HS("TBarCode InForm")	eDecoder_TBarCodeInForm,
} e_Decoder;


//----------------------------------------------------------------------------
///  Type of barcode scanner for which the output should be optimized.
//----------------------------------------------------------------------------
typedef enum 
/// @cond INCLUDE_IN_DOXY
tag_StructuredAppendMode            // This shall not appear in doxygen. Would create a confusing typedef in the doxygen doc.
/// @endcond 
{	
  /// No structured append information is used. The barcode data of multiple barcodes could be
  /// corrupted if the barcodes are scanned in the wrong order.\n
	TECIT_HS("No structured append information")	eSAM_None = 0,
  /// The standard structured append mode of the barcodes is used. This mode allows a barcode 
  /// scanner to append the data of multiple barcodes correctly, even if they are scanned 
  /// in the wrong order. \n
  /// Note: Not all barcodes have a native structured append mode defined in the barcode standard.\n
	TECIT_HS("Use standard structured append method of current symbology")	eSAM_Standard,
  /// A custom structured append mode is used. The data of each barcode begins with 4 special bytes: 
  ///  - Index (1 Byte, beginning with 1 for the first barcode - not a zero-based index) +
  ///  - Total number of barcodes (1 Byte) +
  ///  - Random File ID (2 Bytes) to identify the barcode series.
  /// This information is supported by TEC-IT's barcode scanning solution TBarCode InForm and can be used
  /// in custom barcode scanner applications.
  TECIT_HS("Use custom structured append info (symbology-independent)")	eSAM_TBarCode,
} e_StructuredAppendMode;


//----------------------------------------------------------------------------
/// Type of compression used for content of barcode.
/// \note Compression should only be used with barcodes which support binary data
//----------------------------------------------------------------------------
typedef enum 
/// @cond INCLUDE_IN_DOXY
tag_Compression            // This shall not appear in doxygen. Would create a confusing typedef in the doxygen doc.
/// @endcond 
{	
  /// Barcode data is not compressed.
	TECIT_HS("No Compression")	eCompression_None = 0,
  /// Barcode data is compressed with the Deflate algorithm (RFC 1951).
	TECIT_HS("Deflate (RFC 1951)")	eCompression_Deflate,
  /// Barcode data is compressed with the GZip algorithm (RFC 1952).
  TECIT_HS("GZip (RFC 1952)")	eCompression_GZip,
  /// Barcode data is compressed with the ZLib algorithm (RFC 1950).
  TECIT_HS("ZLib (RFC 1950)")	eCompression_ZLib,
}
e_Compression;


//----------------------------------------------------------------------------
/// GDI drawing method.
/// Drawing bars by the rectangle drawing function can lead to sub-optimal 
/// output quality. Therefore, TBarCode usually uses advanced drawing
/// methods for more accurate barcodes.
/// Due to incompatibilities with certain printer drivers the user can switch 
/// to the compatible mode or the dual mode instead.
//----------------------------------------------------------------------------
typedef enum 
/// @cond INCLUDE_IN_DOXY
tag_DrawMode            // This shall not appear in doxygen. Would create a confusing typedef in the doxygen doc.
/// @endcond 
{	
  /// Use the default GDI drawing method.\n
	TECIT_HS("Default")	eDrawMode_Default = 0,
  /// Use the GDI rectangle functions to draw bars. 
  /// It may result in sub-optimal output quality, but is compatible to nearly all printers.\n
	TECIT_HS("Use the compatible GDI draw mode (rectangles).") eDrawMode_Compatible,
  /// Use the advanced GDI draw mode. This method results in the best quality but 
  /// may not be supported by all applications or printers.\n
  TECIT_HS("Use advanced GDI functions (better quality)")	eDrawMode_Advanced,
  /// A combination of the GDI drawing methods is used. This method produces correct
  /// output in most applications and printers but might decrease drawing speed.\n
  TECIT_HS("Use the dual draw mode - a combination of compatible and advanced modes (fail-safe variant)") eDrawMode_Dual,
} e_DrawMode;


//----------------------------------------------------------------------------
/// Type of bounding rectangle.
/// By default the bounding rectangle is static (constant extents).\n
/// Bounding rectangles can be changed to dynamic bounding rectangles which
/// can grow horizontally or vertically.
//----------------------------------------------------------------------------
typedef enum 
/// @cond INCLUDE_IN_DOXY
tag_DynamicBoundingRect            // This shall not appear in doxygen. Would create a confusing typedef in the doxygen doc.
/// @endcond 
{	
  /// The bounding rectangle cannot grow.
	TECIT_HS("Static (fixed) Bounding Rectangle")	eDynamicBoundingRect_None = 0,	
  /// The bounding rectangle can grow horizontally.
  TECIT_HS("Bounding rectangle grows horizontally")	eDynamicBoundingRect_Horizontal,
  /// The bounding rectangle can grow vertically.
  TECIT_HS("Bounding rectangle grows vertically") eDynamicBoundingRect_Vertical,
} e_DynamicBoundingRect;


//---------------------------------------------------------------------------
/// Determines how the size of the barcode and the single modules are set.
//---------------------------------------------------------------------------
typedef enum 
/// @cond INCLUDE_IN_DOXY
tag_SizeMode            // This shall not appear in doxygen. Would create a confusing typedef in the doxygen doc.
/// @endcond 
{
  /// Default size mode.
  /// The size mode is chosen automatically depending on the other barcode settings:
  /// If module width is set (DLL: function BCSetModWidth(); OCX: property TBarCode9Lib::ITBarCodeBase::ModuleWidth), then #eSizeMode_CustomModuleWidth is used; otherwise #eSizeMode_FitToBoundingRect.\n
  TECIT_HS("Use default mode.")	eSizeMode_Default = -1,
  /// The biggest barcode that fits into the bounding rectangle is chosen.\n
  TECIT_HS("Let the barcode fit to the bounding rectangle.") eSizeMode_FitToBoundingRect,
  /// The barcode size is determined by the module width, which is set by
  /// BCSetModWidth() and BCSetModWidthN() (DLL) or TBarCode9Lib::ITBarCodeBase::ModuleWidth (OCX).\n
  TECIT_HS("Use custom module width.")	eSizeMode_CustomModuleWidth,
  /// The barcode size is determined by the module width. A minimal module width is automatically calculated for
  /// a given resolution and optimized for the barcode decoder. 
  /// The output/scanning resolution has to be set with BCSetDPI() (DLL) or TBarCode9Lib::ITBarCodeBase::Dpi (OCX). 
  /// The type of barcode decoder has to be set with BCSetDecoder() (DLL) or TBarCode9Lib::ITBarCodeBase::Decoder (OCX).\n
  TECIT_HS("Auto-calculate minimal module width.")	eSizeMode_MinimalModuleWidth,
} e_SizeMode;

//---------------------------------------------------------------------------
/// Determines the data encoding mode. The data encoding mode specifies how
/// TBarCode interprets the input data. The meaning of each item differs
/// in dependence on whether the input data is Unicode or single byte encoded.
/// See the descriptions below.
//---------------------------------------------------------------------------
typedef enum 
/// @cond INCLUDE_IN_DOXY
tag_EncodingMode            // This shall not appear in doxygen. Would create a confusing typedef in the doxygen doc.
/// @endcond 
{
  /// =0: The input string is converted to the selected code page.
  /// (See also DLL: function BCGet/BCSetCodePage, OCX: property TBarCode9Lib::ITBarCode::CodePage).\n
	TECIT_HS("Convert Input String to Code Page.") eEncMode_CodePage	= 0,   

  /// =1: The input string is treated as a sequence of ASCII characters ranging from 0 to 255. 
  /// If the input data is UNICODE, only the Lower Byte is encoded. If the input data is
  /// single byte encoded, it is used as it is ==> no conversion is done. 
  /// In single byte encoding there is no difference 
  /// between #eEncMode_LowByte, #eEncMode_ByteStream, or #eEncMode_BYTE_HILO.\n
	TECIT_HS("Encode Lower Byte.") eEncMode_LowByte,   

  /// =2: The input string is treated as byte stream. If the input data is UNICODE, 
  /// 16-bit characters in the input stream are interpreted as two ASCII characters
  /// This encoding mode is used for encoding binary and (untranslated) UNICODE data. 
  /// If the input data is single byte encoded, it is used as it is ==> no conversion is done. 
  /// In single byte encoding there is no difference 
  /// between #eEncMode_LowByte, #eEncMode_ByteStream, or #eEncMode_BYTE_HILO.\n
	TECIT_HS("Encode as Byte stream (Low+High Byte).") eEncMode_ByteStream,
  
  /// =3: The input string is treated as byte stream. This item has a similar effect as 
  /// #eEncMode_ByteStream, but if the input data is UNICODE, higher and lower byte 
  /// of the UNICODE character are exchanged.
  /// If the input data is single byte encoded, it is used as it is ==> no conversion is done. 
  /// In single byte encoding there is no difference 
  /// between #eEncMode_LowByte, #eEncMode_ByteStream, or #eEncMode_BYTE_HILO.\n
	TECIT_HS("Encode as Reverse Byte stream (High+Low Byte).") eEncMode_BYTE_HILO,
} e_EncodingMode;

//---------------------------------------------------------------------------
/// Predefined code pages. If the encoding mode (#e_EncodingMode) has the value
/// #eEncMode_CodePage, the input data is encoded in the selected code page.
/// (See also DLL: function BCGet/BCSetCodePage, OCX: property TBarCode9Lib::ITBarCode::CodePage).\n
/// Otherwise (if the encoding mode is different) the code page is ignored.
/// (See also DLL: function BCGet/BCSetEncodingMode, OCX: property TBarCode9Lib::ITBarCode::EncodingMode).
/// The items listed here are predefined values for often used code pages. The programmer
/// can use this data type but is not limited to it. TBarCode supports all code pages that are provided
/// by the operating system.
//---------------------------------------------------------------------------
typedef enum 
/// @cond INCLUDE_IN_DOXY
tag_CodePage            // This shall not appear in doxygen. Would create a confusing typedef in the doxygen doc.
/// @endcond 
{
  /// =0: Custom Code Page. None of the predefined values is used, but the code page is passed directly by the property CodePageCustom. 
	TECIT_HS("Default Code Page") eCodePage_Custom,

  /// =1: Default Code Page. The default code page for the selected barcode type is used. 
  /// PDF417/MicroPDF     ... CP437\n
  /// QR-Code             ... Shift JIS\n
  /// All other barcodes  ... ANSI.\n
	TECIT_HS("Default Code Page") eCodePage_Default,   

  /// =2: ANSI Code Page 
  /// (use the ANSI code page from the setting "Language for non-Unicode programs").\n
	TECIT_HS("ANSI")	eCodePage_ANSI,

  /// =3: Windows-1252 (1252).
  TECIT_HS("Windows-1252 (1252)") eCodePage_Windows1252,

  /// =4: ISO 8859-1 Latin I (28591).
  TECIT_HS("ISO 8859-1 Latin I (28591)") eCodePage_Latin_I,

  /// =5: ASCII Extended (437).
  TECIT_HS("ASCII Extended (437)") eCodePage_ASCIIExt_437,

  /// =6: UTF-8 Code Page.
  TECIT_HS("UTF-8") eCodePage_UTF8,
  
  /// =7: Korean (949).
	TECIT_HS("Korean (949)") eCodePage_Korean,
  
  /// =8: Japanese / Shift-JIS (932).
  TECIT_HS("Japanese / Shift-JIS (932)") eCodePage_Japanese_Shift_JIS,
  
  /// =9: Simplified Chinese (936).
  TECIT_HS("Simplified Chinese (936)")	eCodePage_Simplified_Chinese,
  
  /// =10: Traditional Chinese (950).
  TECIT_HS("Traditional Chinese (950)")	eCodePage_Trad_Chinese_Big5,
  
  /// =11: ANSI - Cyrillic (1251).
  TECIT_HS("ANSI - Cyrillic (1251)") eCodePage_ANSI_Cyrillic,
  
  /// =12: Russian KOI8-R (20866).
  TECIT_HS("Russian KOI8-R (20866)") eCodePage_KOI8_R,
} e_CodePage;

#endif // !__TECBCEnum_H
#endif // !__TBarCode_h__ (See remark above.)


  
  

