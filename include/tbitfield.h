// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.h - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#ifndef __BITFIELD_H__
#define __BITFIELD_H__

#include <iostream>

using namespace std;

typedef unsigned int TELEM;

class TBitField
{
private:
	int  BitLen; // длина битового поля - макс. к-во битов
	TELEM* pMem; // память для представления битового поля
	int  MemLen; // к-во эл-тов Мем для представления бит.поля

	// методы реализации
	int   GetMemIndex(const int n) const; // индекс в pМем для бита n       (#О2)
	TELEM GetMemMask(const int n) const; // битовая маска для бита n       (#О3)
public:
	TBitField(int _BitLen = 32);                //                                   (#О1)
	TBitField(const TBitField& c);    //                                   (#П1)
	~TBitField();                      //                                    (#С)

	// доступ к битам
	int GetLength(void) const;      // получить длину (к-во битов)           (#О)
	void SetBit(const int n);       // установить бит                       (#О4)
	void ClrBit(const int n);       // очистить бит                         (#П2)
	int  GetBit(const int n) const; // получить значение бита               (#Л1)

	// битовые операции
	int operator==(const TBitField& c) const; // сравнение                 (#О5)
	int operator!=(const TBitField& c) const; // сравнение
	TBitField& operator=(const TBitField& c); // присваивание              (#П3)
	TBitField  operator|(const TBitField& c); // операция "или"            (#О6)
	TBitField  operator&(const TBitField& c); // операция "и"              (#Л2)
	TBitField  operator~(void);                // отрицание                  (#С)

	friend istream& operator>>(istream& istr, TBitField& c);       //      (#О7)
	friend ostream& operator<<(ostream& ostr, const TBitField& c); //      (#П4)
};


#endif
