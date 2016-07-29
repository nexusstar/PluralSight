# Design Patterns in C++ Creational

  Design patterns are universally relevant

## SOLID design principles

### Single Responsibility Principle (SRP)

  Class should only have a single responsibility

### Open-Closed Principle (OCP)

  Entities should be open for extension but closed for modification

### Liskov Substitution Principle (LSP)

  Objects should be replaceable with instances of their subtypes without altering
  program correctness

### Interface segregation Principle(ISP)

  Many client-specific interfaces better than one general-purpose interface

### Dependency Inversion Principle (DIP)

 Dependencies should be abstract rather than concrete

 * High-level modules should not depend on low-level modules. Both should depend
 on abstractions.

   Example: reporting component should depend on a ConsoleLogger, but can depend on a ILoger

* Abstraction should not depend on detail. Detail should depend upon abstraction.

* Inversion of Control(IoC) - the actual process of creating abstractions and
getting them to replace dependencies.

* Dependency Injection - use of software frameworks to ensure that a component's
dependencies are satisfied.
