#include "spreadsheet.hpp"
#include "spreadsheet.cpp"
#include "gtest/gtest.h"
#include "select.hpp"
#include <iostream>

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(Select_Contains, duplicateColumn){
	Spreadsheet sheet;
	std::stringstream strm;
   sheet.set_column_names({"First","Last","Age","Major", "Major"});
    sheet.add_row({"Vishal","Menon","19","cs", "cs"});
    sheet.add_row({"Nuha","Rahman","34","agroecology", "cs"});
    sheet.add_row({"Isabelle","Fischer","20","cs", "math"});
    sheet.add_row({"Ben", "Margolis", "23", "audio eng", "bio"}); 
    sheet.set_selection(new Select_Contains(&sheet,"Major","cs"));
    sheet.print_selection(strm);
    EXPECT_EQ(strm.str(), "Vishal Menon 19 cs cs \nIsabelle Fischer 20 cs math \n");
    std::cout << std::endl;
}
TEST(Select_Contains, emptyEntry){
	 Spreadsheet sheet; 
	std::stringstream strm; 
 	sheet.set_column_names({"First", "Last", "Age", "Major"}); 
	sheet.add_row({"Ben", "", "19", "cs"}); 
        sheet.add_row({"Zeke", "Margolis", "12", "physics"}); 
	sheet.set_selection(new Select_Contains(&sheet, "Last", ""));
	sheet.print_selection(strm);  
	EXPECT_EQ(strm.str(), "Ben  19 cs \nZeke Margolis 12 physics \n"); 
	std::cout << std::endl;        
}
TEST(Select_Contains, fakeColumn){ 
	  Spreadsheet sheet;
        std::stringstream strm;
        sheet.set_column_names({"First", "Last", "Age", "Major"});
        sheet.add_row({"Ben", "Margolis", "19", "cs"});
        sheet.add_row({"Zeke", "Margolis", "12", "physics"});
        sheet.set_selection(new Select_Contains(&sheet, "LastName", "Margolis"));
        sheet.print_selection(strm);
        EXPECT_EQ(strm.str(), "");            
        std::cout << std::endl;	
}
TEST(Select_Or, printOr){
	Spreadsheet sheet;
	std:: stringstream strm;
    	sheet.set_column_names({"Name","DOB","Zodiac"});
    	sheet.add_row({"Maisha","040601","Aries"});
    	sheet.add_row({"Ariq","111010","Scorpio"});
    	sheet.add_row({"Izzy","111213","Scorpio"});
    	sheet.add_row({"Nuha","030302","Pisces"});
        sheet.set_selection(new Select_Or(new Select_Contains(&sheet,"Zodiac","Scorpio"), new Select_Contains(&sheet,"DOB","02")));
        sheet.print_selection(strm);
        EXPECT_EQ(strm.str(), "Ariq 111010 Scorpio \nIzzy 111213 Scorpio \nNuha 030302 Pisces \n");
        std::cout << std::endl;
}
TEST(Select_Not, compositeNot){  
	Spreadsheet sheet; 
	std::stringstream strm; 
	sheet.set_column_names({"First", "Last", "Age"});
	sheet.add_row({"Harriet", "Tubman", "40"}); 
	sheet.add_row({"William", "Shakespeare", "65"}); 
	sheet.add_row({"Shahidur", "Rahman", "40"}); 
	sheet.set_selection(new Select_Not(new Select_Not(new Select_Contains(&sheet, "Age", "40")))); 
	sheet.print_selection(strm); 
	EXPECT_EQ(strm.str(), "Harriet Tubman 40 \nShahidur Rahman 40 \n"); 
	std::cout << std::endl; 
}
TEST(Print_Selection, emptySheet) { 
	Spreadsheet sheet; 
	std::stringstream strm; 
	sheet.set_column_names({"First", "Last"}); 
	sheet.set_selection(new Select_Contains(&sheet, "First", "ed")); 
	sheet.print_selection(strm); 
	EXPECT_EQ(strm.str(), ""); 	
	std::cout << std::endl; 
}
TEST(Print_Selection, entireSheet) { 
	Spreadsheet sheet; 
	std::stringstream strm; 
	sheet.set_column_names({"First", "Last", "Age"});
	sheet.add_row({"Nuha", "Rahman", "20"}); 
	sheet.add_row({"Saif", "Rahman", "27"});
	sheet.add_row({"KC", "Rahman", "27"});
	sheet.add_row({"Izabella", "Hintzman", "19"}); 
        sheet.print_selection(strm);
        EXPECT_EQ(strm.str(), "Nuha Rahman 20 \nSaif Rahman 27 \nKC Rahman 27 \nIzabella Hintzman 19 \n");
        std::cout << std::endl;
}
TEST(Select_And, CompositeAnd) { 
	Spreadsheet sheet;
        std::stringstream strm;
        sheet.set_column_names({"First", "Last", "Age"});
        sheet.add_row({"Nuha", "Rahman", "20"});
        sheet.add_row({"Saif", "Rahman", "27"});
        sheet.add_row({"KC", "Rahman", "27"});
        sheet.add_row({"Izabella", "Hintzman", "19"});
	sheet.set_selection(new Select_And(new Select_And(new Select_Contains(&sheet, "Age","29"), new Select_Contains(&sheet, "Last", "Raz")), new Select_Contains(&sheet, "First", "Her"))); 
	sheet.print_selection(strm); 
	EXPECT_EQ(strm.str(), "");
	std::cout << std::endl; 
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



