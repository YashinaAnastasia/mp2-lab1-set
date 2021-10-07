// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//

// Битовое поле

#include "tbitfield.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);

TBitField::TBitField(int _BitLen)
{
    if (_BitLen < 0) throw _BitLen;
    else {
        BitLen = _BitLen;
        MemLen = (_BitLen - 1) / 32 + 1;
        pMem = new TELEM[MemLen];
        for (int i = 0; i < MemLen; i++)
            pMem[i] = 0;
    }
}

TBitField::TBitField(const TBitField& c) // конструктор копирования
{
    MemLen = c.MemLen;
    BitLen = c.BitLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
        pMem[i] = c.pMem[i];
}

TBitField::~TBitField() // деструктор
{
    delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    if ((n < 0) || (n > BitLen))
        throw n;
    else
        return(n / (sizeof(TELEM) * 8));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    if ((n < 0) || (n > BitLen))
        throw n;
    else
    {
        int size = n % (sizeof(TELEM) * 8);
        TELEM mask = 1;
        mask = (mask << size);
        return (mask);
    }
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
    return (BitLen);
}

void TBitField::SetBit(const int n) // установить бит
{
    if ((n < 0) || (n > BitLen))
        throw n;
    else
    {
        int m = GetMemIndex(n);
        TELEM mask = GetMemMask(n);
        pMem[m] = (pMem[m] | mask);
    }
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if ((n < 0) || (n > BitLen))
        throw n;
    else
    {
        int m = GetMemIndex(n);
        TELEM mask = GetMemMask(n);
        pMem[m] = (pMem[m] & ~mask);
    }
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if ((n < 0) || (n > BitLen))
        throw n;
    else
    {
        int m = GetMemIndex(n); // ищем ячейку
        TELEM mask = GetMemMask(n); // маска на эту ячейку
        int result = (mask & pMem[m]);
        if (result == 0)
            return(0);
        else
            return(1);
    }
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& c) // присваивание
{
    if (&c == this)
        return *this;
    BitLen = c.BitLen;
    if (MemLen != c.MemLen)
    {
        MemLen = c.MemLen;
        delete[] pMem;
        pMem = new TELEM[MemLen];
    }
    for (int i = 0; i < MemLen; i++)
        pMem[i] = c.pMem[i];
    return *this;
}

int TBitField::operator==(const TBitField& c) const // сравнение
{
    if (BitLen != c.BitLen)
        return 0;
    else
    {
        for (int i = 0; i < BitLen; i++)
            if (GetBit(i) != c.GetBit(i))
                return 0;
        return 1;
    }
}

int TBitField::operator!=(const TBitField& c) const // сравнение
{
    if (BitLen != c.BitLen)
        return 1;
    else
    {
        for (int i = 0; i < BitLen; i++)
            if (GetBit(i) != c.GetBit(i))
                return 1;
        return 0;
    }
}

TBitField TBitField::operator|(const TBitField& c) // операция "или"
{
    if (BitLen == c.BitLen)
    {
        TBitField tmp(BitLen);
        for (int i = 0; i < BitLen; i++)
        {
            int tmpval = (GetBit(i) || c.GetBit(i));
            if (tmpval == 0)
                tmp.ClrBit(i);
            else
                tmp.SetBit(i);
        }
        return tmp;
    }
    else
    {
        if (BitLen > c.BitLen)
        {
            TBitField tmp(BitLen);
            for (int i = 0; i < c.BitLen; i++)
            {
                int tmpval = (GetBit(i) || c.GetBit(i));
                if (tmpval == 0)
                    tmp.ClrBit(i);
                else
                    tmp.SetBit(i);
            }
            for (int i = c.BitLen; i < BitLen; i++)
                if (GetBit(i) == 1)
                    tmp.SetBit(i);
                else
                    tmp.ClrBit(i);
            return tmp;
        }
        else
        {
            TBitField tmp(c.BitLen);
            for (int i = 0; i < BitLen; i++)
            {
                int tmpval = (GetBit(i) || c.GetBit(i));
                if (tmpval == 0)
                    tmp.ClrBit(i);
                else
                    tmp.SetBit(i);
            }
            for (int i = BitLen; i < c.BitLen; i++)
                if (c.GetBit(i) == 1)
                    tmp.SetBit(i);
                else
                    tmp.ClrBit(i);
            return tmp;
        }
    }
}

TBitField TBitField::operator&(const TBitField& c) // операция "и"
{
    if (BitLen == c.BitLen)
    {
        TBitField tmp(BitLen);
        for (int i = 0; i < BitLen; i++)
        {
            int tmpval = (GetBit(i) && c.GetBit(i));
            if (tmpval == 0)
                tmp.ClrBit(i);
            else
                tmp.SetBit(i);
        }
        return tmp;
    }
    else
    {
        if (BitLen > c.BitLen)
        {
            TBitField tmp(BitLen);
            for (int i = 0; i < c.BitLen; i++)
            {
                int tmpval = (GetBit(i) && c.GetBit(i));
                if (tmpval == 0)
                    tmp.ClrBit(i);
                else
                    tmp.SetBit(i);
            }
            for (int i = c.BitLen; i < BitLen; i++)
                tmp.ClrBit(i);
            return tmp;
        }
        else
        {
            TBitField tmp(c.BitLen);
            for (int i = 0; i < BitLen; i++)
            {
                int tmpval = (GetBit(i) && c.GetBit(i));
                if (tmpval == 0)
                    tmp.ClrBit(i);
                else
                    tmp.SetBit(i);
            }
            for (int i = BitLen; i < c.BitLen; i++)
                tmp.ClrBit(i);
            return tmp;
        }
    }
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField tmp(BitLen);
    for (int i = 0; i < MemLen; i++)
        tmp.pMem[i] = ~pMem[i];
    return tmp;
}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& c) // ввод
{
    int i = 0;
    while ((i >= 0) && (i < c.BitLen))
    {
        c.SetBit(i);
        istr >> i;
    }
    return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& c) // вывод
{
    for (int i = 0; i < c.BitLen; i++)
        ostr << c.GetBit(i);
    return ostr;
}
