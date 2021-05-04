 
#include <iostream>  
#include "gtest/gtest.h"
#include "spreadsheet.cpp"

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
	



int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}


