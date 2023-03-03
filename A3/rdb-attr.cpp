#include <iostream>
#include <vector>
#include <list>
#include <tuple>
#include "rdb.h"

// derived classes of Attr
integerAttribute::integerAttribute(int v) { value = v; }
void integerAttribute::setValue(int v) { value = v; }
int integerAttribute::getValue() const { return value; }
void integerAttribute::printValue() { cout << value; }
bool integerAttribute::operator==(const Attr &right) { return value == ((integerAttribute &)right).value; }
bool integerAttribute::operator!=(const Attr &right) { return value != ((integerAttribute &)right).value; }
bool integerAttribute::operator<=(const Attr &right) { return value <= ((integerAttribute &)right).value; }
bool integerAttribute::operator>=(const Attr &right) { return value >= ((integerAttribute &)right).value; }
bool integerAttribute::operator<(const Attr &right) { return value < ((integerAttribute &)right).value; }
bool integerAttribute::operator>(const Attr &right) { return value > ((integerAttribute &)right).value; }

floatAttribute::floatAttribute(float v) { value = v; }
void floatAttribute::setValue(float v) { value = v; }
float floatAttribute::getValue() const { return value; }
void floatAttribute::printValue() { cout << value; }
bool floatAttribute::operator==(const Attr &right) { return value == ((floatAttribute &)right).value; }
bool floatAttribute::operator!=(const Attr &right) { return value != ((floatAttribute &)right).value; }
bool floatAttribute::operator<=(const Attr &right) { return value <= ((floatAttribute &)right).value; }
bool floatAttribute::operator>=(const Attr &right) { return value >= ((floatAttribute &)right).value; }
bool floatAttribute::operator<(const Attr &right) { return value < ((floatAttribute &)right).value; }
bool floatAttribute::operator>(const Attr &right) { return value > ((floatAttribute &)right).value; }

stringAttribute::stringAttribute(string v) { value = v; }
void stringAttribute::setValue(string v) { value = v; }
string stringAttribute::getValue() const { return value; }
void stringAttribute::printValue() { cout << value; }
bool stringAttribute::operator==(const Attr &right) { return value == ((stringAttribute &)right).value; }
bool stringAttribute::operator!=(const Attr &right) { return value != ((stringAttribute &)right).value; }
bool stringAttribute::operator<=(const Attr &right) { return value <= ((stringAttribute &)right).value; }
bool stringAttribute::operator>=(const Attr &right) { return value >= ((stringAttribute &)right).value; }
bool stringAttribute::operator<(const Attr &right) { return value < ((stringAttribute &)right).value; }
bool stringAttribute::operator>(const Attr &right) { return value > ((stringAttribute &)right).value; }

