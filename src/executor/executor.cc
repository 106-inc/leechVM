#include "executor/executor.hh"

namespace leech {
StackFrame::StackFrame(const FuncMeta *pmeta) : pmeta_(pmeta) {
  if (pmeta_ == nullptr)
    throw std::invalid_argument("Creating stack frame w/ Null func meta");

  for (auto &name : pmeta_->names)
    vars_.emplace(name, nullptr);
}

void StackFrame::push(pLeechObj obj) {
  if (nullptr == obj)
    throw std::invalid_argument("Trying to push nullptr into stackframe");

  dataStack_.push(std::move(obj));
}

State::State(LeechFile *pfile) : pFile(pfile) {
  if (nullptr == pFile)
    throw std::invalid_argument("Trying to execute null leech file");
  auto &meta = pFile->meta;
  auto *mainFrame = &meta.funcs.at(std::string(kMainFuncName));
  pc = mainFrame->addr;
  funcStack.emplace(mainFrame);
}

void Executor::execute() {
  auto &fStack = state_.funcStack;
  while (fStack.size() != 0) {
    auto curInst = state_.getInst(state_.pc);

    state_.nextPC.reset();

    execMap_.at(curInst.getOpcode())(curInst, state_);

    state_.pc = state_.nextPC.value_or(state_.pc + 1);
  }
}

const std::unordered_map<Opcodes, ExecFunc> Executor::execMap_{
    {Opcodes::LOAD_CONST,
     [](const Instruction &inst, State &state) {
       auto &curFrame = state.getCurFrame();
       curFrame.push(curFrame.getConst(inst.getArg())->clone());
     }},
    {Opcodes::STORE_FAST,
     [](const Instruction &inst, State &state) {
       auto &curFrame = state.getCurFrame();
       auto name = curFrame.getName(inst.getArg());
       curFrame.setVar(name, curFrame.top()->clone());
     }},
    {Opcodes::LOAD_FAST,
     [](const Instruction &inst, State &state) {
       auto &curFrame = state.getCurFrame();
       auto name = curFrame.getName(inst.getArg());
       curFrame.push(curFrame.getVar(name)->clone());
     }},
    {Opcodes::COMPARE_OP, [](const Instruction &inst, State &state) {
       auto &curFrame = state.getCurFrame();
       auto op = static_cast<CmpOp>(inst.getArg());
       auto tos1 = curFrame.popGetTos();
       auto tos2 = curFrame.popGetTos();

       bool res = tos1->compare(tos2.get(), op);

       curFrame.emplace<IntObj>(res);
     }}};
} // namespace leech
