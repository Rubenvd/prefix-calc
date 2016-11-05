#include "prefixcalc.h"
#include "gtest/gtest.h"

bool closeEnough(float a, float b){
    float c = a - b;
    return (c * c) < 0.001;
}

TEST(PrefixCalc, ConstructorNoVal)
{
    try{
        PrefixCalc("");
    }catch(std::string){}
}

TEST(PrefixCalc, ConstructorSingleDigit)
{
    PrefixCalc("4");
}

TEST(PrefixCalc, ConstructorComma)
{
    PrefixCalc("4.2");
}

TEST(PrefixCalc, ConstructorCommaBefore)
{
    PrefixCalc(".4");
}

TEST(PrefixCalc, ConstructorCommaAfter)
{
    PrefixCalc("4.");
}

TEST(PrefixCalc, ConstructorNormalMultiple)
{
    PrefixCalc("* 1 3");
}

TEST(PrefixCalc, ConstructorNormalDivide)
{
    PrefixCalc("/ 1 3");
}

TEST(PrefixCalc, ConstructorNormalMinus)
{
    PrefixCalc("- 1 3");
}

TEST(PrefixCalc, ConstructorNormalPlus)
{
    PrefixCalc("+ 1 3");
}

TEST(PrefixCalc, ConstructorDivideByZero)
{
    PrefixCalc("/ 4 0");
}

TEST(PrefixCalc, ConstructorIncomplete)
{
    try{
        PrefixCalc("/ 4");
        FAIL();
    }catch(std::string){}
}

TEST(PrefixCalc, ConstructorBadOperand)
{
    try{
        PrefixCalc("/ 4 a");
        FAIL();
    }catch(std::string){}
}

TEST(PrefixCalc, ConstructorBadOperator)
{
    try{
        PrefixCalc("a 4 9");
        FAIL();
    }catch(std::string){}
}

TEST(PrefixCalc, NormalMultiple)
{
    PrefixCalc calc("* 1 3");
    ASSERT_TRUE(closeEnough(calc.getValue(), 3));
}

TEST(PrefixCalc, NormalDivide)
{
    PrefixCalc calc("/ 1 3");
    ASSERT_TRUE(closeEnough(calc.getValue(), 1.0/3.0));
}

TEST(PrefixCalc, NormalMinus)
{
    PrefixCalc calc("- 1 3");
    ASSERT_TRUE(closeEnough(calc.getValue(), -2));
}

TEST(PrefixCalc, NormalPlus)
{
    PrefixCalc calc("+ 1 3");
    ASSERT_TRUE(closeEnough(calc.getValue(), 4));
}

TEST(PrefixCalc, DivideByZero)
{
    PrefixCalc zero("/ 4 0");
    try{
        zero.getValue();
        FAIL();
    }catch(std::string){}
}

TEST(PrefixCalc, DivideByIndirectZero)
{
    PrefixCalc zeroIndirect("/ 4 - 2 2");
    try{
        zeroIndirect.getValue();
        FAIL();
    }catch(std::string){}
}

TEST(PrefixCalc, CheckValue)
{
    PrefixCalc calc1("/ 4 2");
    ASSERT_TRUE(closeEnough(calc1.getValue(), 2));
}

TEST(PrefixCalc, CheckValueRightIsOtherCalc)
{
    PrefixCalc calc2("/ 4 - 2 1");
    ASSERT_TRUE(closeEnough(calc2.getValue(), 4));
}

TEST(PrefixCalc, CheckValueLeftIsOtherCalc)
{
    PrefixCalc calc3("* 4 2");
    ASSERT_TRUE(closeEnough(calc3.getValue(), 8));
}

TEST(PrefixCalc, CheckValueBothAreOtherCalc)
{
    PrefixCalc calc4("* * 2 2 - 8 3");
    ASSERT_TRUE(closeEnough(calc4.getValue(), 20));
}

TEST(PrefixCalc, CommaNumber)
{
    PrefixCalc calc("* 2.2 2.2");
    ASSERT_TRUE(closeEnough(calc.getValue(), 4.84));
}

TEST(PrefixCalc, Negatives)
{
    PrefixCalc calc("* -2 2");
    ASSERT_TRUE(closeEnough(calc.getValue(), -4));
}

TEST(PrefixCalc, NegativeAndNegative)
{
    PrefixCalc calc("* -2 -2");
    ASSERT_TRUE(closeEnough(calc.getValue(), 4));
}

TEST(PrefixCalc, NegativeComma)
{
    PrefixCalc calc("* -2 2.2");
    ASSERT_TRUE(closeEnough(calc.getValue(), -4.4));
}

TEST(PrefixCalc, NegativeAndNegativeComma)
{
    PrefixCalc calc("* -2.2 -2.2");
    ASSERT_TRUE(closeEnough(calc.getValue(), 4.84));
}

TEST(PrefixCalc, NegativeInMiddle)
{
    try{
        PrefixCalc calc("2-2");
        FAIL();
    }catch(std::string){}
}

TEST(PrefixCalc, DoubleComma)
{
    try{
        PrefixCalc calc("2..2");
        FAIL();
    }catch(std::string){}
}

TEST(PrefixCalc, NegativeAtEnd)
{
    try{
        PrefixCalc calc("2-");
        FAIL();
    }catch(std::string){}
}

TEST(PrefixCalc, DotInBeginning)
{
    PrefixCalc calc(".2");
    ASSERT_TRUE(closeEnough(calc.getValue(), 0.2));
}

TEST(PrefixCalc, DotAtEnd)
{
    PrefixCalc calc("2.");
    ASSERT_TRUE(closeEnough(calc.getValue(), 2));
}

TEST(PrefixCalc, MultipleDigits)
{
    PrefixCalc calc("-3355.131");
    ASSERT_TRUE(closeEnough(calc.getValue(), -3355.131));
}

TEST(PrefixCalc, containsX)
{
    PrefixCalc("X");
}

TEST(PrefixCalc, constainsXInCalc)
{
    PrefixCalc("* X 1");
}

TEST(PrefixCalc, XinCalc)
{
    try {
        PrefixCalc calc("* 4 X/");
        FAIL();
    } catch (std::string) {}
}
TEST(PrefixCalc, XinNum)
{
    try {
        PrefixCalc calc("* 4 X8");
        FAIL();
    } catch (std::string) {}
}
TEST(PrefixCalc, multipleX)
{
    try {
        PrefixCalc calc("* X X");
        FAIL();
    } catch (std::string) {}
}

TEST(PrefixCalc, getSimpleX)
{
    PrefixCalc calc("X");
    ASSERT_TRUE(closeEnough(calc.getValueIfXIs(4), 4));
}

TEST(PrefixCalc, getCalcedX)
{
    PrefixCalc calc("* 2 X");
    ASSERT_TRUE(closeEnough(calc.getValueIfXIs(8), 16));
}

TEST(PrefixCalc, getComplicatedX)
{
    PrefixCalc calc("- 4 * + X 5 9");
    ASSERT_TRUE(closeEnough(calc.getValueIfXIs(4), -77));
}
