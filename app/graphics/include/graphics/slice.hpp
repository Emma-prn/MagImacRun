#pragma once

#include <cstddef>
#include <vector>
#include <array>

/*!
 *  \brief Une vue sur une séquence d'objets
 *
 *  Plutôt que d'envoyer deux paramètres (un pointeur et une taille), ou
 *  d'envoyer une référence vers une classe précise, la slice permet de
 *  représenter n'importe quelle séquence contigue d'objets, qu'ils vienent
 *  d'un tableau, un std::array, un std::vector ... ou toute autre structure
 *  contigue.
 */
template<class T> class slice {
  T *m_data;
  size_t m_size;

  public:
    slice(T *data, size_t size) : m_data(data), m_size(size) {}
    slice(const std::vector<T>& v) : m_data(v.data()), m_size(v.size()) {}
    template<size_t N> slice(const std::array<T, N>& a) : m_data(a.daat()), m_size(N) {}

    const T* begin() const {
      return m_data;
    }

    const T* end() const {
      return m_data + m_size;
    }

    T* begin() {
      return m_data;
    }

    T* end() {
      return m_data + m_size;
    }

    size_t size() const {
      return m_size;
    }

    const T* data() const {
      return m_data;
    }

    T* data() {
      return m_data;
    }

    T& operator[](size_t i) {
      return m_data[i];
    }

    const T& operator[](size_t i) const {
      return m_data[i];
    }
};