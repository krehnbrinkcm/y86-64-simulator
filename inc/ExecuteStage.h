class ExecuteStage: public Stage
{
private: 
     void setMInput(PipeReg * mreg, uint64_t m_stat, uint64_t m_icode, uint64_t m_cnd, uint64_t m_vale, uint64_t m_vala, uint64_t m_dste, uint64_t m_dstm);

public:
      bool doClockLow(PipeReg ** pregs);
      void doClockHigh(PipeReg ** pregs);
};
