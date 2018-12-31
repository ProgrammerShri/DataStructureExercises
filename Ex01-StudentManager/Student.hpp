#pragma once
#include <fstream>
#include <iostream>
#include <string>

class Student
{
public:
    Student() {}
    Student(uint32_t _id, std::string _name, std::string _gender, uint8_t _age, std::string _exam_type)
        : id(_id), name(_name), gender(_gender), age(_age), exam_type(_exam_type) {}

    friend std::istream& operator>>(std::istream& is, Student& stu);
    friend std::ostream& operator<<(std::ostream& os, const Student& stu);

    friend std::ofstream& operator<<(std::ofstream& ofs, const Student& stu);

    unsigned id;
    std::string name;
    std::string gender;
    unsigned age;
    std::string exam_type;
};

std::istream& operator>>(std::istream& is, Student& stu)
{
    is >> stu.id >> stu.name >> stu.gender >> stu.age >> stu.exam_type;
    return is;
}

std::ostream& operator<<(std::ostream& os, const Student& stu)
{
    os << stu.id << "\t" << stu.name << "\t" << stu.gender << "\t" << stu.age << "\t" << stu.exam_type;
    return os;
}

std::ofstream& operator<<(std::ofstream& ofs, const Student& stu)
{
    ofs << stu.id << "," << stu.name << "," << stu.gender << "," << stu.age << "," << stu.exam_type;
    return ofs;
}