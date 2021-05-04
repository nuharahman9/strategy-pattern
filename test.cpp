#include "spreadsheet.hpp"
#include "spreadsheet.cpp"
#include "gtest/gtest.h"
#include "select.hpp"
#include <iostream>

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(Spreadsheet, RegularPrint){
	Spreadsheet sheet;
	std:: stringstream output;
    sheet.set_column_names({"First","Last","Age","Major"});
    sheet.add_row({"Amanda","Andrews","22","business"});
    sheet.add_row({"Brian","Becker","21","computer science"});
    sheet.add_row({"Carol","Conners","21","computer science"});

    sheet.print_selection(output);
    EXPECT_EQ(output.str(), "Amanda Andrews 22 business \nBrian Becker 21 computer science \nCarol Conners 21 computer science \n");
    std::cout << std::endl;
}

TEST(Select_Contains, Print2){
	Spreadsheet sheet;
	sheet.set_column_names({"First"});
	sheet.add_row({"Bob"});
	sheet.add_row({"John"});
	sheet.add_row({"Tom"});
	sheet.set_selection(new Select_Contains(&sheet,"First","Bob"));
	std::stringstream output;
	sheet.print_selection(output);
	std::string str = output.str();
	ASSERT_EQ(str,"Bob \n");
}

TEST(Select_Contains, UppercaseFirstName){
	Spreadsheet sheet;
	std:: stringstream output;
    sheet.set_column_names({"First","Last","Age","Major"});
    sheet.add_row({"Amanda","Andrews","22","business"});
    sheet.add_row({"Brian","Becker","21","computer science"});
    sheet.add_row({"Carol","Conners","21","computer science"});

    sheet.set_selection(new Select_Contains(&sheet,"First","A"));
    sheet.print_selection(output);
    EXPECT_EQ(output.str(), "Amanda Andrews 22 business \n");
    std::cout << std::endl;
}

TEST(Select_Contains, empty){
	Spreadsheet sheet;
	std:: stringstream output;
    sheet.set_column_names({"First","Last","Age","Major"});
    sheet.add_row({"Amanda","Andrews","22","business"});
    sheet.add_row({"Brian","Becker","21","computer science"});
    sheet.add_row({"Carol","Conners","21","computer science"});

    sheet.set_selection(new Select_Contains(&sheet,"Major",""));
    sheet.print_selection(output);
    EXPECT_EQ(output.str(), "Amanda Andrews 22 business \nBrian Becker 21 computer science \nCarol Conners 21 computer science \n");
    std::cout << std::endl;
}

TEST(Select_Contains, sameLetter){
	Spreadsheet sheet;
	std:: stringstream output;
    sheet.set_column_names({"First","Last","Age","Major"});
    sheet.add_row({"Amanda","Andrews","22","business"});
    sheet.add_row({"Brian","Becker","21","computer science"});
    sheet.add_row({"Carol","Conners","21","computer science"});

    sheet.set_selection(new Select_Contains(&sheet,"First","a"));
    sheet.print_selection(output);
    EXPECT_EQ(output.str(), "Amanda Andrews 22 business \nBrian Becker 21 computer science \nCarol Conners 21 computer science \n");
    std::cout << std::endl;
}

TEST(Select_And, Full){
        Spreadsheet sheet;
        sheet.set_column_names({"First"});
        sheet.add_row({"apple"});
        sheet.add_row({"apples"});
        sheet.add_row({"Apple"});
        sheet.set_selection(new Select_And(new Select_Contains(&sheet,"First","p"),new Select_Contains(&sheet,"First","l")));
        std::stringstream output;
        sheet.print_selection(output);
        std::string str = output.str();
        ASSERT_EQ(str,"apple \napples \nApple \n");
}

TEST(Select_And, EmptyString){
        Spreadsheet sheet;
        sheet.set_column_names({"First"});
        sheet.add_row({"apple"});
        sheet.add_row({"apples"});
        sheet.add_row({"Apple"});
        sheet.set_selection(new Select_And(new Select_Contains(&sheet,"First","a"),new Select_Contains(&sheet,"First","A")));
        std::stringstream output;
        sheet.print_selection(output);
        std::string str = output.str();
        ASSERT_EQ(str,"");
}

TEST(Select_Or, Full){
        Spreadsheet sheet;
        sheet.set_column_names({"First"});
        sheet.add_row({"apple"});
        sheet.add_row({"apples"});
        sheet.add_row({"Apple"});
        sheet.set_selection(new Select_Or(new Select_Contains(&sheet,"First","a"),new Select_Contains(&sheet,"First","A")));
        std::stringstream output;
        sheet.print_selection(output);
        std::string str = output.str();
        ASSERT_EQ(str,"apple \napples \nApple \n");
}

TEST(Select_Or, EmptyString){
        Spreadsheet sheet;
        sheet.set_column_names({"First"});
        sheet.add_row({"apple"});
        sheet.add_row({"apples"});
        sheet.add_row({"Apple"});
        sheet.set_selection(new Select_Or(new Select_Contains(&sheet,"First","ewq"),new Select_Contains(&sheet,"First","xe")));
        std::stringstream output;
        sheet.print_selection(output);
        std::string str = output.str();
        ASSERT_EQ(str,"");
}

TEST(Select_Not, EmptyString){
        Spreadsheet sheet;
        sheet.set_column_names({"First"});
        sheet.add_row({"apple"});
        sheet.add_row({"apples"});
        sheet.add_row({"Apple"});
        sheet.set_selection(new Select_Not(new Select_Contains(&sheet,"First","pp")));
        std::stringstream output;
        sheet.print_selection(output);
        std::string str = output.str();
        ASSERT_EQ(str,"");
}


