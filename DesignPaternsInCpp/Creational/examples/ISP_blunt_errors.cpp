// Interface Segregation Principle
// No client should be forced to depend on methods it does not use
#include <vector>

struct Document;
struct IMachine
{
  virtual void print(std::vector<Document*> docs) = 0;
  virtual void scan(std::vector<Document*> docs) = 0;
  virtual void fax(std::vector<Document*> docs) = 0;
};

// we force implementer and client to use too much
// maybe something that she does need

struct MFP : IMachine
{
  void print(std::vector<Document*> docs) override;
  void scan(std::vector<Document*> docs) override;
  void fax(std::vector<Document*> docs) override;
};

// instead we could implement
// some separate interfaces
struct IPrinter
{
  virtual void print(std::vector<Document*> docs) = 0;
};

struct IScaner
{
  virtual void scan(std::vector<Document*> docs) = 0;
};

// And if we need we implement what we need
struct Printer : IPrinter
{
  void  print(std::vector<Document*> docs) override;
};

struct Scaner : IScaner
{
  void scan(std::vector<Document*> docs) override;
};

// and what if someone ask for the whole machine
//
// First we define one abstraction
struct IMAchine : IPrinter, IScaner {};

struct Machine : IMachine
{
  IPrinter& printer;
  IScaner& scaner;

  Machine(IPrinter& printer, IScaner& scaner):
    printer{printer},
    scaner{scaner}
  {}

  void print(std::vector<Document*> docs) override{
    printer.print(docs);
  }
  void scan(std::vector<Document*> docs) override{
    scaner.scan(docs);
  }
};

