#include "tset.h"
#include "tbitfield.h"

TSet::TSet(int mp = 100) : BitField(mp), MaxPower(mp) {}

// конструктор копирования
TSet::TSet(const TSet& s) : BitField(s.MaxPower)
{
	MaxPower = s.MaxPower;
	BitField = s.BitField;
}

// конструктор преобразования типа
TSet::TSet(const TBitField& c) : BitField(c.GetLength())
{
	BitField = c;
	MaxPower = c.GetLength();
}

// оператор преобразования типа 
TSet::operator TBitField()
{
	return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet& s) // присваивание
{
	BitField = s.BitField;
	MaxPower = s.MaxPower;
	return *this;
}

int TSet::operator==(const TSet& s) const // сравнение
{
	if ((MaxPower == s.MaxPower) && (BitField == s.BitField))
		return 1;
	else
		return 0;
}

int TSet::operator!=(const TSet& s) const // сравнение
{
	if ((MaxPower == s.MaxPower) && (BitField == s.BitField))
		return 0;
	else
		return 1;
}

TSet TSet::operator+(const TSet& s) // объединение
{
	if (MaxPower > s.MaxPower)
	{
		TBitField tmp(MaxPower);
		tmp = BitField | s.BitField;
		TSet _S(tmp);
		return _S;
	}
	else
	{
		TBitField tmp(s.MaxPower);
		tmp = BitField | s.BitField;
		TSet _S(tmp);
		return _S;
	}
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	TSet tmp(*this);
	tmp.BitField.SetBit(Elem);
	return tmp;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	TSet tmp(*this);
	tmp.BitField.ClrBit(Elem);
	return (tmp);
}

TSet TSet::operator*(const TSet& s) // пересечение
{
	TBitField tmp(MaxPower);
	tmp = BitField & s.BitField;
	TSet _s(tmp);
	return _s;
}

TSet TSet::operator~(void) // дополнение
{
	TSet tmp(MaxPower);
	tmp.BitField = ~BitField;
	return tmp;
}

// перегрузка ввода/вывода

istream& operator>>(istream& istr, TSet& s) // ввод
{
	int i = 0;
	while ((i >= 0) && (i < s.MaxPower))
	{
		s.InsElem(i);
		istr >> i;
	}
	return istr;
}

ostream& operator<<(ostream& ostr, const TSet& s) // вывод
{
	for (int i = 0; i < s.MaxPower; i++)
		if (s.BitField.GetBit(i))
			ostr << i;
	return ostr;
}