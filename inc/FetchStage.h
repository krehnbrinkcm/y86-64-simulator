//class to represent the Fetch stage

class FetchStage: public Stage
{
   private:
      //TODO: provide declarations for new methods
	uint64_t selectPC(PipeReg * freg, PipeReg * mreg, PipeReg * wreg);
	bool needRegIds(uint64_t f_icode);
	void getRegIds(uint64_t byte, uint64_t &rA, uint64_t &rB);
        bool needValC(uint64_t f_icode);
	uint64_t buildValC(int64_t f_pc, uint64_t icode); 
	uint64_t predictPC(uint64_t f_icode, uint64_t f_valc, uint64_t f_valp);
	uint64_t PCincrement(uint64_t f_pc, bool needRegId, bool needValC);
      //set the input value for each fieldof the D pipeline register
      void setDInput(PipeReg * dreg, uint64_t stat, uint64_t icode, 
                     uint64_t ifun, uint64_t rA, uint64_t rB,
                     uint64_t valC, uint64_t valP);
   public:
      //These are the only methods that are called outside of the class
      bool doClockLow(PipeReg ** pregs);  
      void doClockHigh(PipeReg ** pregs);
};
