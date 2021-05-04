#ifndef __SELECT_HPP__
#define __SELECT_HPP__

#include <cstring>
#include <iostream> 
class Select
{
public:
    virtual ~Select() = default;

    // Return true if the specified row should be selected.
    virtual bool select(const Spreadsheet* sheet, int row) const = 0;
};

// A common type of criterion for selection is to perform a comparison based on
// the contents of one column.  This class contains contains the logic needed
// for dealing with columns. Note that this class is also an abstract base
// class, derived from Select.  It introduces a new select function (taking just
// a string) and implements the original interface in terms of this.  Derived
// classes need only implement the new select function.  You may choose to
// derive from Select or Select_Column at your convenience.
class Select_Column: public Select
{
protected:
    int column;
public:
    Select_Column(const Spreadsheet* sheet, const std::string& name)
    {
        column = sheet->get_column_by_name(name);
    }

    virtual bool select(const Spreadsheet* sheet, int row) const
    {
        return select(sheet->cell_data(row, column));
    }

    // Derived classes can instead implement this simpler interface.
    virtual bool select(const std::string& s) const = 0;
};

class Select_Contains: public Select_Column {
protected: 	
   std::string name; 
public:  
   Select_Contains(const Spreadsheet* sheet, const std::string& clnm, const std::string& nm) : Select_Column{sheet, clnm}  { 
      name = nm;
   }
//~Select_Contains()  
   bool select(const std::string& s) const { 
	 if (name.find(s) != std::string::npos) { 
          return true; 
        
      }
      return false; 	
   }

      
 };

class Select_Not: public Select { 
protected: 
  const Select* not1; 
public: 
  Select_Not(const Select* no1) { 
     not1 = no1; 
  }
  ~Select_Not() { 
     delete not1; 
  } 
  bool select(const Spreadsheet* sheet, int row) const { 
       if (not1->select(sheet, row) == false) { 
             return true; 
        }
      return false; 
  }

}; 
class Select_And: public Select { 
protected: 
   const Select* and1; 
   const Select* and2; 
public:   
   Select_And(const Select* an1, const Select* an2) { 
      and1 = an1; 
      and2 = an2; 
   }
   ~Select_And() { 
      delete and1; 
      delete and2; 
   }

   bool select(const Spreadsheet* sheet, int row) const { 
      if (and1->select(sheet, row) && and2->select(sheet, row)) { 
         return true;        
      }
      return false; 

   }
 
}; 
class Select_Or: public Select { 
protected: 
  const Select* or1; 
  const Select* or2; 
public:     
  Select_Or(const Select* o1, const Select* o2) { 
     or1 = o1; 
     or2 = o2; 
  }

  ~Select_Or() { 
     delete or1; 
     delete or2; 
  }

  bool select(const Spreadsheet* sheet, int row) const { 
     if (or1->select(sheet, row) || or2->select(sheet, row)) { 
	return true; 
      }
     return false; 
  }

};  


#endif //__SELECT_HPP__
