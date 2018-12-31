#pragma once
#include <exception>
#include <fstream>
#include <ios>
#include <iostream>
#include <string>
#include "../Common/LinkedList.hpp"
#include "Student.hpp"

class StudentManager
{
public:
    void run();

private:
    void init();
    void insert();
    void remove();
    void find();
    void modify();
    void stat();
    void exportToCSV();

    bool duplicate(unsigned id);
    void printTable();

    ds::LinkedList<Student> table;
};

void StudentManager::run()
{
    while (table.empty()) {
        init();
    }
    while (true) {
        printTable();
        int op;
        std::cout << "[1]插入\t[2]删除\t[3]查找\t[4]修改" << std::endl
                  << "[5]统计\t[6]导出\t\t[0]退出" << std::endl
                  << std::endl
                  << "请选择你要进行的操作：";
        std::cin >> op;
        if (!std::cin.good()) {
            std::cin.clear();
            op = -1;  // set op to UINT32_MAX to get a warning
        }
        std::cin.ignore(INT32_MAX, '\n');
        switch (op) {
            case 0:
                std::cout << "正在退出..." << std::endl;
                return;
            case 1:
                insert();
                break;
            case 2:
                remove();
                break;
            case 3:
                find();
                break;
            case 4:
                modify();
                break;
            case 5:
                stat();
                break;
            case 6:
                exportToCSV();
                break;
            default:
                std::cout << "[警告] 输入有误，请重新输入" << std::endl;
                continue;
        }
    }
}

void StudentManager::init()
{
    size_t stu_count;
    Student temp;
    std::cout << "首先请建立考生信息系统！" << std::endl
              << "请输入考生人数：";
    std::cin >> stu_count;
    if (!std::cin.good()) {
        std::cin.clear();
        stu_count = 0;
    }
    std::cin.ignore(INT32_MAX, '\n');
    if (stu_count <= 0) {
        std::cout << "[错误] 考生人数需为大于0的整数" << std::endl
                  << std::endl;
        return;
    }
    std::cout << "请依次输入考生的考号、姓名、性别、年龄及报考类别:" << std::endl;
    for (unsigned i = 0; i < stu_count; i++) {
        try {
            std::cin >> temp;
            std::cin.ignore(INT32_MAX, '\n');
            if (duplicate(temp.id)) {
                throw std::invalid_argument("重复的考号");
            }
            table.push_back(temp);
        }
        catch (const std::invalid_argument& e) {
            std::cout << "[警告] " << e.what() << "，该条目将会被忽略" << std::endl
                      << "[信息] 考号必须唯一！" << std::endl;
        }
    }
}

void StudentManager::insert()
{
    try {
        size_t position;
        std::cout << "提示：插入功能为向前插入，若要向末尾添加，请输入最大序号的下一个数字" << std::endl
                  << "请输入你要插入的考生的位置：";
        std::cin >> position;
        std::cin.ignore(INT32_MAX, '\n');
        if (position == 0 || position > (table.size() + 1)) {
            throw std::out_of_range("输入超出范围");
        }
        Student newStu;
        std::cout << "请依次输入要插入的考生的考号、姓名、性别、年龄及报考类别:" << std::endl;
        std::cin >> newStu;
        std::cin.ignore(INT32_MAX, '\n');
        if (duplicate(newStu.id)) {
            throw std::invalid_argument("重复的考号");
        }
        if (position == (table.size() + 1)) {
            table.push_back(newStu);
        }
        else {
            table.insert((position - 1), newStu);
        }
    }
    catch (const std::out_of_range& e) {
        std::cout << "[错误] " << e.what() << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::cout << "[警告] " << e.what() << "，该条目将会被忽略" << std::endl
                  << "[信息] 考号必须唯一！" << std::endl;
    }
}

void StudentManager::remove()
{
    try {
        size_t position;
        std::cout << "请输入你要删除的考生的序号：";
        std::cin >> position;
        std::cin.ignore(INT32_MAX, '\n');
        if (position == 0 || position > table.size()) {
            throw std::out_of_range("输入超出范围");
        }
        std::cout << "你删除的考生信息是：" << std::endl
                  << "考号\t姓名\t性别\t年龄\t报考类别" << std::endl
                  << table.at(position - 1) << std::endl;
        table.erase(position - 1);
    }
    catch (const std::out_of_range& e) {
        std::cout << "[错误] " << e.what() << std::endl;
    }
}

void StudentManager::find()
{
    unsigned id;
    std::cout << "请输入你要查找的考生的考号：";
    std::cin >> id;
    std::cin.ignore(INT32_MAX, '\n');
    auto node = table.begin();
    while (node != nullptr) {
        if (id == node->data.id) {
            std::cout << "考号\t姓名\t性别\t年龄\t报考类别" << std::endl
                      << node->data << std::endl;
            return;  // since id is unique, return when found one
        }
        node = node->next;
    }
    std::cout << "未找到，请确认输入信息是否正确" << std::endl;
}

void StudentManager::modify()
{
    try {
        size_t position;
        std::cout << "请输入你要修改的考生的序号：";
        std::cin >> position;
        std::cin.ignore(INT32_MAX, '\n');
        if (position == 0 || position > table.size()) {
            throw std::out_of_range("输入超出范围");
        }
        Student newStu;
        std::cout << "请依次输入修改后的考生的考号、姓名、性别、年龄及报考类别:" << std::endl;
        std::cin >> newStu;
        std::cin.ignore(INT32_MAX, '\n');
        if (duplicate(newStu.id)) {
            throw std::invalid_argument("重复的考号");
        }
        table.at(position - 1) = newStu;
    }
    catch (const std::out_of_range& e) {
        std::cout << "[错误] " << e.what() << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::cout << "[警告] " << e.what() << "，该条目将会被忽略" << std::endl
                  << "[信息] 考号必须唯一！" << std::endl;
    }
}

void StudentManager::stat()
{
    std::cout << "共有" << table.size() << "条数据" << std::endl;
}

void StudentManager::exportToCSV()
{
    std::string filename;
    std::cout << "请输入导出文件名(不需要扩展名)：";
    std::cin >> filename;
    std::cin.ignore(INT32_MAX, '\n');
    filename.append(".csv");
    std::ofstream file(filename, std::ios::out);
    file << "考号,姓名,性别,年龄,报考类别" << std::endl;
    auto node = table.begin();
    while (node != nullptr) {
        file << node->data << std::endl;
        node = node->next;
    }
    file.close();
    std::cout << filename << " 导出成功" << std::endl;
}

bool StudentManager::duplicate(unsigned id)
{
    if (table.empty()) {
        return false;
    }
    auto node = table.begin();
    while (node != nullptr) {
        if (id == node->data.id) {
            return true;
        }
        node = node->next;
    }
    return false;
}

void StudentManager::printTable()
{
    std::cout << std::endl
              << "序号\t考号\t姓名\t性别\t年龄\t报考类别" << std::endl;
    auto node = table.begin();
    int i = 1;
    while (node != nullptr) {
        std::cout << i << "\t" << node->data << std::endl;
        node = node->next;
        i++;
    }
    std::cout << std::endl;
}