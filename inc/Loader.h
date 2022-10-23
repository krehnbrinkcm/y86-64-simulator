
class Loader
{
   private:
      int32_t lastAddress;  //last address stored to in memory
      Memory * mem;         //pointer to memory instance
      std::ifstream inf;    //file handle
      String * inputFile;   //pointer to String object containing file name

      bool openFile();      //check file name for correctness and open it
      bool printErrMsg(int32_t, int32_t, String *);  //print error message

      //TODO
      //add declarations for other methods used by your loader
      bool hasData(String);
      uint32_t getData(String); 
      bool hasComm(String);
      bool hasAdd(String);
      String getAdd(String);
      String getComm(String);
      String loadLine(String);
   public:
      //methods called outside of class
      Loader(int argc, char * argv[], Memory * mem);
      bool load();
};
