// Copyright (c) 2019-2025 Cody R. Drisko. All rights reserved.
// Licensed under the MIT License. See the LICENSE file in the project root for more information.
//
// Name: Exercise4_04.cpp
// Author: crdrisko
// Date: 04/25/2020-13:29:09
// Description: Simulate a job interview looking for a candidate with very specific qualifications

#include <cctype>
#include <iostream>

int main()
{
    bool perfectCandidate {false};

    // Age criteria is between 21 and 35 years of age
    int age {};
    std::cout << "Please enter your age in years: ";
    std::cin >> age;

    if (age < 0 || age > 120)
    {
        std::cout << "Invalid answers will not be tolerated, goodbye." << std::endl;
        return 1;
    }

    perfectCandidate = (age > 21 && age < 35);


    // Gender criteria is female
    char gender {};
    std::cout << "Now, what is your gender? ";
    std::cin >> gender;

    gender = std::tolower(gender);

    if (gender != 'm' && gender != 'f')
    {
        std::cout << "Invalid answers will not be tolerated, goodbye." << std::endl;
        return 1;
    }

    perfectCandidate &= (gender == 'f');


    // Degree criteria is bachelors or masters degree
    enum class AcademicDegree : char
    {
        none         = 'n',
        associate    = 'a',
        bachelor     = 'b',
        professional = 'p',
        master       = 'm',
        doctor       = 'd'
    };
    AcademicDegree degree {};

    char tempDegree {};
    std::cout << "Enter the first letter of your highest degree earned, possible values are:"
              << "\n\t'n' for no degree "
              << "\n\t'a' for associates"
              << "\n\t'b' for bachelors"
              << "\n\t'p' for professional"
              << "\n\t'm' for masters"
              << "\n\t'd' for doctorate\n";
    std::cin >> tempDegree;

    // Validate user input
    switch (tempDegree)
    {
    case 'n':
        degree = AcademicDegree::none;
        break;
    case 'a':
        degree = AcademicDegree::associate;
        break;
    case 'b':
        degree = AcademicDegree::bachelor;
        break;
    case 'p':
        degree = AcademicDegree::professional;
        break;
    case 'm':
        degree = AcademicDegree::master;
        break;
    case 'd':
        degree = AcademicDegree::doctor;
        break;

    default:
        std::cout << "Invalid answers will not be tolerated, goodbye." << std::endl;
        return 1;
    }

    perfectCandidate &= (degree == AcademicDegree::bachelor || degree == AcademicDegree::master);


    // Married criteria is unmarried
    bool married {};
    char tempMarried {};
    std::cout << "Okay, just a few more questions, Please respond with y or n.\n"
              << "Are you married? ";
    std::cin >> tempMarried;

    switch (std::tolower(tempMarried))
    {
    case 'y':
        married = true;
        break;
    case 'n':
        married = false;
        break;
    default:
        std::cout << "Invalid answers will not be tolerated, goodbye." << std::endl;
        return 1;
    }

    perfectCandidate &= (!married);


    // Language criteria is speaks Hindi or Urdu
    bool speaksHindi {}, speaksUrdu {};
    char tempSpeaksHindi {};
    std::cout << "Okay, just a few more questions, Please respond with y or n.\n"
              << "Do you speak Hindi? ";
    std::cin >> tempSpeaksHindi;

    switch (std::tolower(tempSpeaksHindi))
    {
    case 'y':
        speaksHindi = true;
        break;
    case 'n':
        speaksHindi = false;
        break;
    default:
        std::cout << "Invalid answers will not be tolerated, goodbye." << std::endl;
        return 1;
    }

    char tempSpeaksUrdu {};
    std::cout << "Okay, just a few more questions, Please respond with y or n.\n"
              << "Do you speak Urdu? ";
    std::cin >> tempSpeaksUrdu;

    switch (std::tolower(tempSpeaksUrdu))
    {
    case 'y':
        speaksUrdu = true;
        break;
    case 'n':
        speaksUrdu = false;
        break;
    default:
        std::cout << "Invalid answers will not be tolerated, goodbye." << std::endl;
        return 1;
    }

    perfectCandidate &= (speaksHindi || speaksUrdu);


    if (perfectCandidate)
        std::cout << "Congratulations you're hired!" << std::endl;
    else
        std::cout << "We're sorry, you don't match the requirements for this job." << std::endl;
}
