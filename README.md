# stl_compatible_set

### Домашнее задание #5
### Вариант #1
---

### Студент:       Ларкин Егор WEB-11

### Ментор:        Кириллов Денис
 
### Преподаватель: Возвахов Иван   

---
### Задание 

Необходимо реализовать упрощённую версию упорядоченного множества из STL Set<T>. Асимптотики всех операций должны быть аналогичными std::set. Сравнение элементов типа T осуществлять только при помощи оператора <. 
Необходимо поддержать следующие методы:
1) методы жизненного цикла - 4б
- конструктор по умолчанию;
- конструктор, принимающий пару итераторов элементов типа T, последовательно вставляемых в контейнер;
- конструктор, принимающий std::initializer_list элементов типа T;
- конструктор копирования ("глубокое копирование всех узлов контейнера");
- оператор присваивания;
- деструктор;

2) класс должен предоставлять const bidirectional-итератор для доступа к элементам, а также методы begin и end и позволять просматривать все элементы контейнера без возможности их изменения, перемещаясь от каждого к следующему/предыдущему за O(1). Так как контейнер упорядоченный, то подразумевается их перебор в порядке возрастания - 4б;

3) методы insert и erase вставки и удаления элементов из контейнера. Тип возвращаемого значения - void, При наличии/отсутствии элемента ничего делать не нужно. При модификации контейнера любой из этих операций итераторы могут инвалидироваться - 3б;

4) константные методы:
- size и empty, возвращающие количество элементов и true/false в зависимости от наличия элементов в контейнере - 1б;
- find и lower_bound, которые возвращают соответственно итератор на искомый элемент во множестве/первый элемент, который не меньше искомого (или end() при его отсутствии) - 3б.
