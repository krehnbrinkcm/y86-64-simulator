class ExecuteStage: public Stage
{
private:
     uint64_t getAluA(uint64_t e_icode,uint64_t e_valA,uint64_t e_valC); 
     uint64_t getAluB(uint64_t e_icode,uint64_t e_valB);
     uint64_t getAluFun(uint64_t e_icode, uint64_t e_ifun);
     bool set_cc(uint64_t e_icode);
     uint64_t getDstE(uint64_t e_icode, uint64_t e_cnd, uint64_t e_dste);
     uint64_t ALU(uint64_t e_icode, uint64_t e_ifun, uint64_t e_valA, uint64_t e_valB, uint64_t e_valC);
     void CC(uint64_t num, uint64_t A, uint64_t B);
     void setMInput(PipeReg * mreg, uint64_t m_stat, uint64_t m_icode, uint64_t m_cnd, uint64_t m_vale, uint64_t m_vala, uint64_t m_dste, uint64_t m_dstm);

public:
      bool doClockLow(PipeReg ** pregs);
      void doClockHigh(PipeReg ** pregs);
};
