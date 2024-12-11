/// \cond

#include "pch.h"
#include <sstream>
#include "Stud.h" // Include your class header file

TEST(StudentasTest, ConstructorAndAccessors) {
    Studentas zm("Jonas", "Petrauskas");
    EXPECT_EQ(zm.getVardas(), "Jonas");
    EXPECT_EQ(zm.getPavarde(), "Petrauskas");
}

TEST(StudentasTest, ParameterizedConstructor) {
    vector<int> nd = { 8, 9, 10 };
    Studentas studentas("Jonas", "Jonaitis", nd, 9, 8.5, 9.0);
    EXPECT_EQ(studentas.getVardas(), "Jonas");
    EXPECT_EQ(studentas.getPavarde(), "Jonaitis");
    EXPECT_EQ(studentas.getNd(), nd);
    EXPECT_EQ(studentas.getEgz(), 9);
    EXPECT_DOUBLE_EQ(studentas.galutinisBalasVidur, 8.5);
    EXPECT_DOUBLE_EQ(studentas.galutinisBalasMed, 9.0);
}

TEST(StudentasTest, Destructor) {
    Studentas* studentas = new Studentas("Jonas", "Jonaitis");
    delete studentas;
    SUCCEED();
}

TEST(InputOperatorTest, ValidInput) {
    Studentas student;

    std::istringstream input("Jonas\nPavardenis\nT\n");

    input >> student;

    EXPECT_EQ(student.getVardas(), "Jonas");
    EXPECT_EQ(student.getPavarde(), "Pavardenis");

    EXPECT_GT(student.getNd().size(), 0);  
    EXPECT_GE(student.getEgz(), 0);  
    EXPECT_LE(student.getEgz(), 10);

    EXPECT_GE(student.galutinisBalasVidur, 0);
    EXPECT_LE(student.galutinisBalasVidur, 10);
    EXPECT_GE(student.galutinisBalasMed, 0);
    EXPECT_LE(student.galutinisBalasMed, 10);
}
TEST(StudentasTest, OutputOperatorTest) {
    Studentas studentas;
    studentas.setVardas("Jonas");
    studentas.setPavarde("Jonaitis");
    studentas.galutinisBalasVidur = 7.5;  // Example of setting some values
    studentas.galutinisBalasMed = 8.0;

    // Expected output in the format defined by your operator<<
    std::string expected_output = "Jonaitis       Jonas          7.50                8.00                ";

    // Capture the output using a stringstream
    std::ostringstream output;
    output << studentas;

    // Compare the output with the expected string
    EXPECT_EQ(output.str(), expected_output);
}

/// \endcond