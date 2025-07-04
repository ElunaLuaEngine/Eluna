/*
* Copyright (C) 2010 - 2025 Eluna Lua Engine <https://elunaluaengine.github.io/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef BIGINTMETHODS_H
#define BIGINTMETHODS_H

namespace LuaBigInt
{
    template <typename T, typename Op>
    constexpr int PerformOp(Eluna* E, Op op)
    {
        T val1 = E->CHECKVAL<T>(1);
        T val2 = E->CHECKVAL<T>(2);
        E->Push(op(val1, val2));
        return 1;
    }

    template<typename T>
    int Add(Eluna* E, T*)
    {
        return PerformOp<T>(E, std::plus<T>{});
    }

    template<typename T>
    int Subtract(Eluna* E, T*)
    {
        return PerformOp<T>(E, std::minus<T>{});
    }

    template<typename T>
    int Multiply(Eluna* E, T*)
    {
        return PerformOp<T>(E, std::multiplies<T>{});
    }

    template<typename T>
    int Divide(Eluna* E, T*)
    {
        return PerformOp<T>(E, std::divides<T>{});
    }

    template<typename T>
    int Mod(Eluna* E, T*)
    {
        return PerformOp<T>(E, std::modulus<T>{});
    }

    template<typename T>
    int UnaryMinus(Eluna* E, T*)
    {
        T val = E->CHECKVAL<T>(1);
        E->Push(std::negate<T>{}(val));
        return 1;
    }

    template<typename T>
    int Equal(Eluna* E, T*)
    {
        return PerformOp<T>(E, std::equal_to<T>{});
    }

    template<typename T>
    int Less(Eluna* E, T*)
    {
        return PerformOp<T>(E, std::less<T>{});
    }

    template<typename T>
    int LessOrEqual(Eluna* E, T*)
    {
        return PerformOp<T>(E, std::less_equal<T>{});
    }

    template<typename T>
    int ToString(Eluna* E, T*)
    {
        T val = E->CHECKVAL<T>(1);
        std::ostringstream ss;
        ss << val;
        E->Push(ss.str());
        return 1;
    }

    template<typename T>
    int Pow(Eluna* E, T*)
    {
        T val1 = E->CHECKVAL<T>(1);
        T val2 = E->CHECKVAL<T>(2);
        E->Push(static_cast<T>(powl(static_cast<long double>(val1), static_cast<long double>(val2))));
        return 1;
    }

    int Equal(Eluna* E, ObjectGuid*)
    {
        E->Push(E->CHECKVAL<ObjectGuid>(1) == E->CHECKVAL<ObjectGuid>(2));
        return 1;
    }

    int ToString(Eluna* E, ObjectGuid*)
    {
        E->Push(E->CHECKVAL<ObjectGuid>(1).ToString());
        return 1;
    }

    ElunaRegister<long long> LongLongMethods[] =
    {
        { "__add", &LuaBigInt::Add<long long> },
        { "__sub", &LuaBigInt::Subtract<long long> },
        { "__mul", &LuaBigInt::Multiply<long long> },
        { "__div", &LuaBigInt::Divide<long long> },
        { "__mod", &LuaBigInt::Mod<long long> },
        { "__unm", &LuaBigInt::UnaryMinus<long long> },
        { "__eq", &LuaBigInt::Equal<long long> },
        { "__lt", &LuaBigInt::Less<long long> },
        { "__le", &LuaBigInt::LessOrEqual<long long> },
        { "__tostring", &LuaBigInt::ToString<long long> },
        { "__pow", &LuaBigInt::Pow<long long> },
    };

    ElunaRegister<unsigned long long> ULongLongMethods[] =
    {
        { "__sub", &LuaBigInt::Subtract<unsigned long long> },
        { "__mul", &LuaBigInt::Multiply<unsigned long long> },
        { "__div", &LuaBigInt::Divide<unsigned long long> },
        { "__mod", &LuaBigInt::Mod<unsigned long long> },
        { "__eq", &LuaBigInt::Equal<unsigned long long> },
        { "__lt", &LuaBigInt::Less<unsigned long long> },
        { "__le", &LuaBigInt::LessOrEqual<unsigned long long> },
        { "__tostring", &LuaBigInt::ToString<unsigned long long> },
        { "__pow", &LuaBigInt::Pow<unsigned long long> },
    };

    ElunaRegister<ObjectGuid> ObjectGuidMethods[] =
    {
        { "__tostring", &LuaBigInt::ToString },
        { "__eq", &LuaBigInt::Equal },
    };
};

#endif
