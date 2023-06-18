#include <iostream>
#include <string>
#include <vector>

using namespace std;

class MenuItem
{
public:
    MenuItem(string nm) : m_name(nm) {}
    virtual ~MenuItem() {}
    string name() const { return m_name; }
    virtual bool add(MenuItem* m) = 0;
    virtual const vector<MenuItem*>* menuItems() const = 0;
private:
    string m_name;
};

class PlainMenuItem : public MenuItem   // PlainMenuItem allows no submenus
{
public:
    PlainMenuItem(string nm) : MenuItem(nm) {}
    virtual bool add(MenuItem* m) { return false; }
    virtual const vector<MenuItem*>* menuItems() const { return nullptr; }
};

class CompoundMenuItem : public MenuItem  // CompoundMenuItem allows submenus
{
public:
    CompoundMenuItem(string nm) : MenuItem(nm) {}
    virtual ~CompoundMenuItem();
    virtual bool add(MenuItem* m) { m_menuItems.push_back(m); return true; }
    virtual const vector<MenuItem*>* menuItems() const { return &m_menuItems; }
private:
    vector<MenuItem*> m_menuItems;
};

CompoundMenuItem::~CompoundMenuItem()
{
    for (int k = 0; k < m_menuItems.size(); k++)
        delete m_menuItems[k];
}

//*** delete above

void listAll(const MenuItem* m, string path) // two-parameter overload
{
   
    // If the menu does not have a sub menu and has no current path, output its name
    if (m->menuItems() == nullptr && path.size() == 0) {
        cout << m->name() << endl;
        return;
    }

    // If the current path has no name, start with the name of it's name
    if (path.size() == 0) {
        path += m->name();
    }
    
    // If the menu has sub menus, traverse the menu and get the sub item file path and files paths for
    // the sub items of those sub items
    if (m->menuItems() != nullptr) {
        for (int i = 0; i < m->menuItems()->size(); i++) {
            string filePath = path;
            vector<MenuItem*> currentMenu = *m->menuItems();
            if (filePath.size() == 0) {
                filePath += currentMenu[i]->name();
            }
            else filePath += "/" + currentMenu[i]->name();
            cout << filePath << endl;
            listAll(currentMenu[i], filePath);
        }
    }

    //if (m->menuItems() == nullptr && path.size() == 0) {
    //    path += m->name();
    //    cout << path << endl;
    //    
    //    return;
    //}

    //// If m has a sub menu, traverse the items in that submenu and cout those names
    //if (m->menuItems() != nullptr) {
    //    for (int i = 0; i < m->menuItems()->size(); i++) {
    //        string filePath = path;
    //        vector<MenuItem*> currentMenu = *m->menuItems();
    //        if (filePath.size() != 0) {
    //            filePath += "/" + currentMenu[i]->name();
    //        }
    //        else filePath += currentMenu[i]->name();
    //        cout << filePath << endl;

    //        // Check if there is still sub menu items for a give filePath
    //        listAll(currentMenu[i], filePath);
    //    }
    //}

}

//*** delete below

void listAll(const MenuItem* m)  // one-parameter overload
{
    if (m != nullptr)
        listAll(m, "");
}
//
//int main()
//{
//    CompoundMenuItem* cm0 = new CompoundMenuItem("New");
//    cm0->add(new PlainMenuItem("Window"));
//    CompoundMenuItem* cm1 = new CompoundMenuItem("File");
//    cm1->add(cm0);
//    cm1->add(new PlainMenuItem("Open"));
//    cm1->add(new PlainMenuItem("Exit"));
//    CompoundMenuItem* cm2 = new CompoundMenuItem("Help");
//    cm2->add(new PlainMenuItem("Index"));
//    cm2->add(new PlainMenuItem("About"));
//    CompoundMenuItem* cm3 = new CompoundMenuItem("");  // main menu bar
//    cm3->add(cm1);
//    cm3->add(new PlainMenuItem("Refresh"));  // no submenu
//    cm3->add(new CompoundMenuItem("Under Development")); // no submenus yet
//    cm3->add(cm2);
//    listAll(cm3);
//
//    PlainMenuItem* x1 = new PlainMenuItem("HELLLOOOO");
//    listAll(x1);
//    delete x1;
//
//    delete cm3;
//}
