#ifdef DLLDIR_EX
   #define DLLDIR  __declspec(dllexport)
#else
   #define DLLDIR  __declspec(dllimport)
#endif


class DLLDIR Dllclass
{
   public:
      Dllclass();          // Class Constructor
      ~Dllclass();         // Class destructor
      int Dllclass::Hook_Start_Control(int cflag);
};