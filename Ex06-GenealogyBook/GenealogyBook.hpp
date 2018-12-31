#pragma once
#include <exception>
#include <iostream>
#include <string>

using namespace std;

struct Member
{
    string _name;
    Member* parent = nullptr;
    Member* child = nullptr;
    Member* siblingPrev = nullptr;
    Member* siblingNext = nullptr;
};

class GenealogyBook
{
public:
    void run();

private:
    void init();
    void createFamily();
    void addChild();
    void removeFamily();
    void editName();

    Member* find(string name, Member* node);
    void printChild(Member* node);
    void freeNode(Member* node);

    Member* ancestor = nullptr;
};

void GenealogyBook::run()
{
    cout << "**              家谱管理系统              **" << endl
         << "============================================" << endl
         << "**          请选择要执行的操作:           **" << endl
         << "**          A --- 完善家庭                **" << endl
         << "**          B --- 添加家庭成员            **" << endl
         << "**          C --- 解散局部成员            **" << endl
         << "**          D --- 更改家庭成员姓名        **" << endl
         << "**          E --- 退出系统                **" << endl
         << "============================================" << endl;

    init();

    while (true) {
        char op;
        cout << "请选择要执行的操作: ";
        cin >> op;
        if (!cin.good()) {
            cin.clear();
            op = -1;  // get a warning
        }
        cin.ignore(INT32_MAX, '\n');
        switch (op) {
            case 'A':
            case 'a':
                createFamily();
                break;
            case 'B':
            case 'b':
                addChild();
                break;
            case 'C':
            case 'c':
                removeFamily();
                break;
            case 'D':
            case 'd':
                editName();
                break;
            case 'E':
            case 'e':
                cout << "正在退出..." << endl;
                return;
            default:
                cout << "[错误] 输入有误，请重新输入" << endl
                     << endl;
                continue;
        }
    }
}

void GenealogyBook::init()
{
    ancestor = new Member;
    cout << "首先建立一个家谱！" << endl
         << "请输入祖先的姓名: ";
    cin >> ancestor->_name;
    cout << "此家谱的祖先是: " << ancestor->_name << endl;
    cout << endl;
}

void GenealogyBook::createFamily()
{
    try {
        string name;
        cout << "请输入要建立家庭的人的姓名: ";
        cin >> name;
        Member* node = find(name, ancestor);
        if (node == nullptr) {
            throw invalid_argument("找不到" + name);
        }
        if (node->child != nullptr) {
            throw invalid_argument(name + "已建立过家庭");
        }

        int childNum;
        cout << "请输入" << node->_name << "的子女人数: ";
        cin >> childNum;
        if (!cin.good()) {
            cin.clear();
            throw invalid_argument("输入不合法");
        }
        if (childNum == 0) {
            return;
        }
        cout << "请依次输入" << node->_name << "的子女的姓名: ";
        node->child = new Member();
        Member* temp = node->child;
        cin >> temp->_name;
        temp->parent = node;
        for (int i = 1; i < childNum; i++) {
            Member* sibling = new Member();
            cin >> sibling->_name;
            sibling->parent = node;
            sibling->siblingPrev = temp;
            temp->siblingNext = sibling;
            temp = temp->siblingNext;
        }

        printChild(node);
    }
    catch (const invalid_argument& e) {
        cout << "[错误] " << e.what() << ", 请检查输入" << endl;
    }
    cout << endl;
}

void GenealogyBook::addChild()
{
    try {
        string name;
        cout << "请输入要添加子女的人的姓名: ";
        cin >> name;
        Member* node = find(name, ancestor);
        if (node == nullptr) {
            throw invalid_argument("找不到" + name);
        }

        cout << "请输入" << node->_name << "新添加的子女的姓名: ";
        Member* newChild = new Member();
        cin >> newChild->_name;
        newChild->parent = node;
        if (node->child == nullptr) {
            node->child = newChild;
        }
        else {
            Member* temp = node->child;
            while (temp != nullptr) {
                temp = temp->siblingNext;
            }
            newChild->siblingPrev = temp;
            temp->siblingNext = newChild;
        }

        printChild(node);
    }
    catch (const invalid_argument& e) {
        cout << "[错误] " << e.what() << ", 请检查输入" << endl;
    }
    cout << endl;
}

void GenealogyBook::removeFamily()
{
    try {
        string name;
        cout << "请输入要解散家庭的人的姓名: ";
        cin >> name;
        Member* node = find(name, ancestor);
        if (node == nullptr) {
            throw invalid_argument("找不到" + name);
        }
        if (node == ancestor) {
            throw invalid_argument("根节点不允许被删除");
        }

        cout << "要解散家庭的人是: " << node->_name << endl;
        printChild(node);

        if (node->child != nullptr) {
            freeNode(node->child);
        }

        if (node->siblingPrev != nullptr && node->siblingNext != nullptr) {
            node->siblingPrev->siblingNext = node->siblingNext;
            node->siblingNext->siblingPrev = node->siblingPrev;
        }
        else if (node->siblingPrev != nullptr && node->siblingNext == nullptr) {
            node->siblingPrev->siblingNext = nullptr;
        }
        else if (node->siblingPrev == nullptr && node->siblingNext != nullptr) {
            node->siblingNext->siblingPrev = nullptr;
            node->parent->child = node->siblingNext;
        }
        else if (node->siblingPrev == nullptr && node->siblingNext == nullptr) {
            node->parent->child = nullptr;
        }
        delete node;
    }
    catch (const invalid_argument& e) {
        cout << "[错误] " << e.what() << ", 请检查输入" << endl;
    }
    cout << endl;
}

void GenealogyBook::editName()
{
    try {
        string name;
        cout << "请输入要更改姓名的人的目前姓名: ";
        cin >> name;
        Member* node = find(name, ancestor);
        if (node == nullptr) {
            throw invalid_argument("找不到" + name);
        }
        cout << "请输入更改后的姓名: ";
        cin >> node->_name;
        cout << name << "已更名为" << node->_name << endl;
    }
    catch (const invalid_argument& e) {
        cout << "[错误] " << e.what() << ", 请检查输入" << endl;
    }
    cout << endl;
}

// Find member by name
// sibling first, then child
Member* GenealogyBook::find(string name, Member* node)
{
    if (node->_name == name) {
        return node;
    }
    Member* temp = node;
    Member* result = nullptr;
    while (temp->siblingNext != nullptr) {
        result = find(name, temp->siblingNext);
        if (result != nullptr) {
            return result;
        }
    }
    if (node->child != nullptr) {
        result = find(name, node->child);
    }
    return result;
}

void GenealogyBook::printChild(Member* node)
{
    if (node->child == nullptr) {
        cout << node->_name << "没有子女" << endl;
    }
    else {
        Member* temp = node->child;
        cout << node->_name << "的第一代子女是: ";
        while (temp != nullptr) {
            cout << temp->_name << " ";
            temp = temp->siblingNext;
        }
        cout << endl;
    }
}

void GenealogyBook::freeNode(Member* node)
{
    Member* temp = node;
    while (temp->siblingNext != nullptr) {
        temp = temp->siblingNext;
    }
    while (temp->siblingPrev != nullptr) {
        temp = temp->siblingPrev;
        temp->siblingNext->siblingPrev = nullptr;
        temp->siblingNext->siblingNext = nullptr;
        freeNode(temp->siblingNext);
    }
    if (temp->child) {
        freeNode(temp->child);
    }
    delete node;
}