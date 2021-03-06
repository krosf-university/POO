/**
 * @file cadena.hpp
 * @author Carlos Rodrigo Sanabria Flores
 * @date 27 Apr 2018
 * @copyright 2018 Carlos Rodrigo Sanabria Flores
 */
#ifndef CADENA_H
#define CADENA_H
#include <functional>
#include <iostream>

class Cadena {
 public:
  /* CONSTRUCTORES */
  explicit Cadena(size_t t = 0, char c = ' ');  //
  Cadena(const char *cad);
  // Constructor de copia.
  Cadena(const Cadena &cad);
  // Constructor de movimiento.
  Cadena(Cadena &&cad);
  /* METODOS */
  // Metodo para obtener una subcadena.
  Cadena substr(size_t begindex, size_t len) const;
  // Metodo para obtener la logitud de una cadena.
  size_t length() const noexcept { return tam_; }
  // Metodo para convertir una "Cadena" a "const char*".
  const char *c_str() const noexcept { return s_; }
  /* OPERADORES */
  // Operadores indice que no producen exepciones.
  char operator[](size_t j) const noexcept;
  char &operator[](size_t j) noexcept;
  // Operadores indice que producen exepciones.
  char at(size_t i) const;
  char &at(size_t i);
  // Operadores de asignación.
  Cadena &operator+=(const Cadena &cad);
  Cadena &operator=(const Cadena &cad);
  Cadena &operator=(const char *cad);
  Cadena &operator=(Cadena &&cad);
  /* DESTRUCTOR */
  ~Cadena();
  /* ITERADORES */
  using iterator = char *;
  using const_iterator = char const *;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  iterator begin() noexcept { return s_; }
  const_iterator begin() const noexcept { return s_; }
  const_iterator cbegin() const noexcept { return s_; }
  reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
  const_reverse_iterator rbegin() const noexcept {
    return const_reverse_iterator(end());
  }
  const_reverse_iterator crbegin() const noexcept {
    return const_reverse_iterator(end());
  }

  iterator end() noexcept { return s_ + tam_; }
  const_iterator end() const noexcept { return s_ + tam_; }
  const_iterator cend() const noexcept { return s_ + tam_; }
  reverse_iterator rend() noexcept { return reverse_iterator(begin()); }
  const_reverse_iterator rend() const noexcept {
    return const_reverse_iterator(begin());
  }
  const_reverse_iterator crend() const noexcept {
    return const_reverse_iterator(begin());
  }

 private:
  char *s_;
  size_t tam_;
};
// Concatenación con el operador +
Cadena operator+(const Cadena &cad1, const Cadena &cad2);
/* OPERADORES DE COMPARACIÓN */
bool operator==(const Cadena &cad1, const Cadena &cad2) noexcept;
bool operator!=(const Cadena &cad1, const Cadena &cad2) noexcept;
bool operator>(const Cadena &cad1, const Cadena &cad2) noexcept;
bool operator<(const Cadena &cad1, const Cadena &cad2) noexcept;
bool operator<=(const Cadena &cad1, const Cadena &cad2) noexcept;
bool operator>=(const Cadena &cad1, const Cadena &cad2) noexcept;
/* OPERADORES DE FLUJO */
std::ostream &operator<<(std::ostream &os, const Cadena &cad) noexcept;
std::istream &operator>>(std::istream &is, Cadena &cad) noexcept;
/* HASH */
namespace std {
template <>
struct hash<Cadena> {
  size_t operator()(const Cadena &cad) const {
    return hash<std::string>{}(cad.c_str());
  }
};
}  // namespace std
#endif
