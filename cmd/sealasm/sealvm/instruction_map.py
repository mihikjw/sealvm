from typing import Dict

from sealvm.instruction_def import InstructionDef
from sealvm.instructions import Instructions, Type, Size, Mnemonic

InstructionMap: Dict[str, InstructionDef] = {
    # mov
    "MOV_LIT_REG": InstructionDef(Instructions.MOV_LIT_REG, Size.LIT_REG, Type.LIT_REG, Mnemonic.MOV),
    "MOV_REG_REG": InstructionDef(Instructions.MOV_REG_REG, Size.REG_REG, Type.REG_REG, Mnemonic.MOV),
    "MOV_REG_MEM": InstructionDef(Instructions.MOV_REG_MEM, Size.REG_MEM, Type.REG_MEM, Mnemonic.MOV),
    "MOV_MEM_REG": InstructionDef(Instructions.MOV_MEM_REG, Size.MEM_REG, Type.MEM_REG, Mnemonic.MOV),
    "MOV_LIT_MEM": InstructionDef(Instructions.MOV_LIT_MEM, Size.LIT_MEM, Type.LIT_MEM, Mnemonic.MOV),
    "MOV_REG_PTR_REG": InstructionDef(Instructions.MOV_REG_PTR_REG, Size.REG_PTR_REG, Type.REG_PTR_REG, Mnemonic.MOV),
    "MOV_LIT_OFF_REG": InstructionDef(Instructions.MOV_LIT_OFF_REG, Size.LIT_OFF_REG, Type.LIT_OFF_REG, Mnemonic.MOV),

    # arithmetic
    "ADD_REG_REG": InstructionDef(Instructions.ADD_REG_REG, Size.REG_REG, Type.REG_REG, Mnemonic.ADD),
    "ADD_LIT_REG": InstructionDef(Instructions.ADD_LIT_REG, Size.LIT_REG, Type.LIT_REG, Mnemonic.ADD),
    "SUB_REG_LIT": InstructionDef(Instructions.SUB_REG_LIT, Size.REG_LIT, Type.REG_LIT, Mnemonic.SUB),
    "SUB_LIT_REG": InstructionDef(Instructions.SUB_LIT_REG, Size.LIT_REG, Type.LIT_REG, Mnemonic.SUB),
    "SUB_REG_REG": InstructionDef(Instructions.SUB_REG_REG, Size.REG_REG, Type.REG_REG, Mnemonic.SUB),
    "INC_REG": InstructionDef(Instructions.INC_REG, Size.SINGLE_REG, Type.SINGLE_REG, Mnemonic.INC),
    "DEC_REG": InstructionDef(Instructions.DEC_REG, Size.SINGLE_REG, Type.SINGLE_REG, Mnemonic.DEC),
    "MUL_LIT_REG": InstructionDef(Instructions.MUL_LIT_REG, Size.LIT_REG, Type.LIT_REG, Mnemonic.MUL),
    "MUL_REG_REG": InstructionDef(Instructions.MUL_REG_REG, Size.REG_REG, Type.REG_REG, Mnemonic.MUL),

    # logical
    "LSF_REG_LIT": InstructionDef(Instructions.LSF_REG_LIT, Size.REG_LIT, Type.REG_LIT, Mnemonic.LSF),
    "LSF_REG_REG": InstructionDef(Instructions.LSF_REG_REG, Size.REG_REG, Type.REG_REG, Mnemonic.LSF),
    "RSF_REG_LIT": InstructionDef(Instructions.RSF_REG_LIT, Size.REG_LIT, Type.REG_LIT, Mnemonic.RSF),
    "RSF_REG_REG": InstructionDef(Instructions.RSF_REG_REG, Size.REG_REG, Type.REG_REG, Mnemonic.RSF),
    "AND_REG_LIT": InstructionDef(Instructions.AND_REG_LIT, Size.REG_LIT, Type.REG_LIT, Mnemonic.AND),
    "AND_REG_REG": InstructionDef(Instructions.AND_REG_REG, Size.REG_REG, Type.REG_REG, Mnemonic.AND),
    "OR_REG_LIT": InstructionDef(Instructions.OR_REG_LIT, Size.REG_LIT, Type.REG_LIT, Mnemonic.OR),
    "OR_REG_REG": InstructionDef(Instructions.OR_REG_REG, Size.REG_REG, Type.REG_REG, Mnemonic.OR),
    "XOR_REG_LIT": InstructionDef(Instructions.XOR_REG_LIT, Size.REG_LIT, Type.REG_LIT, Mnemonic.XOR),
    "XOR_REG_REG": InstructionDef(Instructions.XOR_REG_REG, Size.REG_REG, Type.REG_REG, Mnemonic.XOR),

    # branching
    "JMP_NOT_EQ": InstructionDef(Instructions.JMP_NOT_EQ, Size.LIT_MEM, Type.LIT_MEM, Mnemonic.JNE),
    "JNE_REG": InstructionDef(Instructions.JNE_REG, Size.REG_MEM, Type.REG_MEM, Mnemonic.JNE),
    "JEQ_REG": InstructionDef(Instructions.JEQ_REG, Size.REG_MEM, Type.REG_MEM, Mnemonic.JEQ),
    "JEQ_LIT": InstructionDef(Instructions.JEQ_LIT, Size.LIT_MEM, Type.LIT_MEM, Mnemonic.JNE),
    "JLT_REG": InstructionDef(Instructions.JLT_REG, Size.REG_MEM, Type.REG_MEM, Mnemonic.JLT),
    "JLT_LIT": InstructionDef(Instructions.JLT_LIT, Size.LIT_MEM, Type.LIT_MEM, Mnemonic.JLT),
    "JGT_REG": InstructionDef(Instructions.JGT_REG, Size.REG_MEM, Type.REG_MEM, Mnemonic.JGT),
    "JGT_LIT": InstructionDef(Instructions.JGT_LIT, Size.LIT_MEM, Type.LIT_MEM, Mnemonic.JGT),
    "JLE_REG": InstructionDef(Instructions.JLE_REG, Size.REG_MEM, Type.REG_MEM, Mnemonic.JLE),
    "JLE_LIT": InstructionDef(Instructions.JLE_LIT, Size.LIT_MEM, Type.LIT_MEM, Mnemonic.JLE),
    "JGE_REG": InstructionDef(Instructions.JGE_REG, Size.REG_MEM, Type.REG_MEM, Mnemonic.JGE),
    "JGE_LIT": InstructionDef(Instructions.JGE_LIT, Size.LIT_MEM, Type.LIT_MEM, Mnemonic.JGE),

    # misc
    "PSH_LIT": InstructionDef(Instructions.PSH_LIT, Size.SINGLE_LIT, Type.SINGLE_LIT, Mnemonic.PSH),
    "PSH_REG": InstructionDef(Instructions.PSH_REG, Size.SINGLE_REG, Type.SINGLE_REG, Mnemonic.PSH),
    "POP": InstructionDef(Instructions.POP, Size.SINGLE_REG, Type.SINGLE_REG, Mnemonic.POP),
    "CAL_LIT": InstructionDef(Instructions.CAL_LIT, Size.SINGLE_LIT, Type.SINGLE_LIT, Mnemonic.CAL),
    "CAL_REG": InstructionDef(Instructions.CAL_REG, Size.SINGLE_REG, Type.SINGLE_REG, Mnemonic.CAL),
    "RET": InstructionDef(Instructions.RET, Size.NO_ARGS, Type.NO_ARGS, Mnemonic.RET),
    "HLT": InstructionDef(Instructions.HLT, Size.NO_ARGS, Type.NO_ARGS, Mnemonic.HLT),
}
