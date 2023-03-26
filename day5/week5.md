object oriented programming
data and functionality is separate
OO languages are imperative

```python
f()
f2()
f3()
...
```

we already had a way to model the world with structure
but this is just a data abstraction

everything can do a function

Fogalomrendszer
- Object:
    - attribute
    - state
    - method 
    - azonossaggal egyezik
    - analogia

```
O:
    string name; // attribute
    int sz[];

    int sum(); // viselkedes
    void f();

O (A, {1,2,3})
O (B, {2,3,4})

O (A, {1,2,3}) 
OID // object id - we don't care about this in the language level
```
object's state can be changed
object's methods
    - can get the state
    - can set the state
object lifetime

# Class
- almost the same as a type
- you can create an object out of a class

# Instance
- class can be instantiated creating an object

```
person          // class
    name
    height
    weight
    move()
    talk()

a = person (A, 2, 100)  // objects
b = person (B, 1.6, 90) // instantiating an person instance

a.move(forward, 1)
```

```
person // but oh no its a different class now
    name
    height
    weight
    hair_color
    hair_length
    move()
    talk()
```
# Oroklodes
superclass <- subclass

person -> person_with_hair
```
person // but oh no its a different class now
    name
    height
    weight
    move()
    talk()

person_with_hair : person
    -weight
    hair_color
    hair_length
    cut_hair()
```
```
class hierarchy
    A 
 /  |  \
B   C   D
    |   |
    E   G
```
subclasses can
- add new attributes
- add new method

superclass cannot manipulate it's subclasses
if a superclass is needed a subclass can be helytettesitett

```
 ^   Animal
 |     |
 |   Mammal
 |   /   \
 |  Dog  Cat
// where I want a mammal we can use a Cat and a Dog
```
single oroklodes
multiple oroklodes

the problem with multiple oroklodes
```
A int z     B double z
  write()     write()
\           /
    C
```
# Encapsulation (bezaras)
- encapsulation 1
    - There is a public and a private part forget this
- encapsulation 2
    - what parts of code can be seen (get; set)

# Polymorphism (tobbalakusag)
object polymorphism
- you can use an object instead of its parent class
method polymorphism
- method override (new implementation of a method)

# Binding (kotes)
modern languages don't have this
```
list<Animal> l = (Cat(), Dog())
for (Animal a : l ) {
    a.move() // static binding: used the superclasses method
             // dynamic: use the lowest classes method
}
```

# Abstract class
classes can't be instantiated. It can only be inherited from
a class is abstract if it has at least one abstract method

# Containers (Contener osztalyok)
Objektumokat tartalmazo lista

# Collection (Kollekcio)
Databases

# Parameter Classes
Generic programming

# Lifetimes
- the programmer does the lifetime
- garbage collection