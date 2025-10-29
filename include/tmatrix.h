// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1)
  {
    if (size <= 0)
      throw out_of_range("Vector size should be greater than zero");
    if (size > MAX_VECTOR_SIZE) {
        throw out_of_range("Exception size");
    }
    sz = size;
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v)
  {
      this->sz = v.sz;
      pMem = new T[sz];
      std::copy(v.pMem, v.pMem + sz, this->pMem);
  }
  TDynamicVector(TDynamicVector&& v) noexcept
  {
      this->sz = v.size();
      this->pMem = v.pMem;
      v.sz = 0;
      v.pMem = nullptr;

  }
  ~TDynamicVector()
  {
      delete[] pMem;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (this != &v) {
          delete[] pMem;
          sz = v.sz;
          pMem = new T[sz];
          std::copy(v.pMem, v.pMem + sz, pMem);
      }
      return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      if (this != &v) {
          delete[] pMem;
          sz = v.sz;
          pMem = v.pMem;
          v.sz = 0;
          v.pMem = nullptr;
      }
      return *this;
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind)
  {
      if (ind >= sz) {
          throw out_of_range("Exception ind is out bound");
      }
      if (ind < 0) {
          throw out_of_range("Exception ind is out bound");
      }
      return pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
      if (ind >= sz) {
          throw out_of_range("Exception ind is out bound");
      }
      if (ind < 0) {
          throw out_of_range("Exception ind is out bound");
      }
      return pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
      if (ind >= sz) {
          throw out_of_range("Exception in control of indexing");
      }
      return pMem[ind];

  }
  const T& at(size_t ind) const
  {
      if (ind >= sz) {
          throw out_of_range("Exception in control of indexing");
      }
      return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (v.sz != sz) {
          return false;

      }
      for (size_t i = 0; i < sz; i++) {
          if (v.pMem[i] != pMem[i]) {
              return false;
          }
      }
      return true;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      if (v.sz != sz) {
          return true;
      }
      for (size_t i = 0; i < sz; i++) {
          if (v.pMem[i] != pMem[i]) {
              return true;
          }
      }
      return false;
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      TDynamicVector vec(sz);
      for (size_t i = 0; i < sz; i++) {
          vec.pMem[i] = pMem[i] + val;
      }
      return vec;
  }
  TDynamicVector operator-(T val)
  {
      TDynamicVector vec(sz);
      for (size_t i = 0; i < sz; i++) {
          vec.pMem[i] = pMem[i] - val;
      }
      return vec;
  }
  TDynamicVector operator*(T val)
  {
      TDynamicVector vec(sz);
      for (size_t i = 0; i < sz; i++) {
          vec.pMem[i] = pMem[i] * val;
      }
      return vec;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (sz != v.sz) {
          throw out_of_range("Exception vec op +");
      }
      TDynamicVector vec(sz);
      for (size_t i = 0; i < sz; i++) {
          vec.pMem[i] = pMem[i] + v.pMem[i];
      }
      return vec;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (sz != v.sz) {
          throw out_of_range("Exception vec op -");
      }
      TDynamicVector vec(sz);
      for (size_t i = 0; i < sz; i++) {
          vec.pMem[i] = pMem[i] - v.pMem[i];
      }
      return vec;
  }
  //T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
  //{
  //    if (sz != v.sz) {
  //        throw out_of_range("Exception vec op *");
  //    }
  //    T res = T();
  //    for (size_t i = 0; i < sz; i++) {
  //        res += pMem[i] * v.pMem[i];
  //    }
  //    return res;

  //}
  T operator*(const TDynamicVector& v)
  {
      if (sz != v.sz) {
          throw out_of_range("Exception vec op *");
      }
      T res = T();
      for (size_t i = 0; i < sz; i++) {
          res += pMem[i] * v.pMem[i];
      }
      return res;

  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
      if (s == 0)
          throw out_of_range("Matrix size should be greater than zero");
      if (s > MAX_MATRIX_SIZE) {
          throw out_of_range("Exception size");
      }
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }
  TDynamicMatrix(const TDynamicVector<TDynamicVector<T>>& mat):TDynamicVector<TDynamicVector<T>>(mat)
  {
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      /*if (sz != m.sz) {
          return false;
      }
      for (size_t i = 0; i < sz; i++) {
          if (pMem[i] != m.pMem[i]) {
              return false;
          }
      }
      return true;*/
      return TDynamicVector<TDynamicVector<T>>::operator==(m);
  }


  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val)
  {
      /*TDynamicMatrix<T> mat(sz);
      for (size_t i = 0; i < sz; i++) {
          mat.pMem[i] = pMem[i] * val;
      }
      return mat;*/
      return TDynamicVector<TDynamicMatrix<T>>::operator*(val);
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      if (sz != v.size()) {
          throw out_of_range("Exception mat op *vec");
      }
      TDynamicVector<T> vec(sz);
      for (size_t i = 0; i < sz; i++) {
          T res = T();
          for (size_t j = 0; j < sz; j++) {
              res += pMem[i][j] * v[j];
          }
          vec[i] = res;
      }
      return vec;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      /*if (sz != m.sz) {
          throw out_of_range("Exception mat op +mat");
      }
      TDynamicMatrix mat(sz);
      for (size_t i = 0; i < sz; i++) {
          mat[i] = pMem[i] + m[i];
      }
      return mat;*/
      return TDynamicVector<TDynamicVector<T>>::operator+(m);
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      /*if (sz != m.sz) {
          throw out_of_range("Exception mat op -mat");
      }
      TDynamicMatrix mat(sz);
      for (size_t i = 0; i < sz; i++) {
          mat[i] = pMem[i] - m[i];
      }
      return mat;*/
      return TDynamicVector<TDynamicVector<T>>::operator-(m);
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      if (sz != m.sz) {
          throw out_of_range("Exception mat op *mat");
      }
      TDynamicMatrix mat(sz);
      for (size_t i = 0; i < sz; i++) {
          for (size_t j = 0; j < sz; j++) {
              T res = T();
              for (size_t k = 0; k < sz; k++) {
                  res += pMem[i][k] * m[k][j];
              }
              mat[i][j] = res;
          }
      }
      return mat;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
      size_t sz;
      istr >> sz;
      v = TDynamicMatrix<T>(sz);
      for (size_t i = 0; i < sz; i++) {
          for (size_t j = 0; j < sz; j++) {
              istr >> v[i][j];
          }
      }
      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.sz; i++) {
          for (size_t j = 0; j < v.sz; j++) {
              ostr << v[i][j] << " ";
          }
          ostr << "\n";
      }
      return ostr;

  }
};

#endif
