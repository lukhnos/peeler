#include <iostream>
#include <set>
#include <string>
#include <vector>
#include "OVCINDataTable.h"
#include "Mandarin.h"

using namespace Formosa::Mandarin;
using namespace OpenVanilla;
using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 3) {
        cerr << "usage: dbgen <bpmf.cin> <bpmf-ext.cin>" << endl;
        return 1;
    }
    
    OVCINDataTableParser p1;    
    OVCINDataTable *b1 = 0;
    b1 = p1.CINDataTableFromFileName(argv[1]);
    if (!b1) {
        cerr << "Invalid file or no such file: " << argv[1] << endl;
        return 1;
    }
    
    OVCINDataTableParser p2;
    OVCINDataTable *b2 = 0;
    b2 = p2.CINDataTableFromFileName(argv[2]);
    if (!b2) {
        cerr << "Invalid file or no such file: " << argv[2] << endl;
    }
    
    OVWildcard w("*");
    vector<pair<string, string> > allB1 = b1->findChardefWithWildcard(w);
    vector<pair<string, string> > allB2 = b2->findChardefWithWildcard(w);
    set<string> originalBig5Set;
    
    for (vector<pair<string, string> >::const_iterator i = allB1.begin(),
        e = allB1.end() ; i != e ; ++i)
    {
        originalBig5Set.insert((*i).second);
    }
    
    const BopomofoKeyboardLayout *kl =
        BopomofoKeyboardLayout::StandardLayout();

    for (vector<pair<string, string> >::const_iterator i = allB2.begin(),
        e = allB2.end() ; i != e ; ++i)
    {
        BPMF bpmf = kl->syllableFromKeySequence((*i).first);
        bool inBig5 = (originalBig5Set.find((*i).second) !=
            originalBig5Set.end());
        
        cout << (*i).second << " " << bpmf.composedString() << " "
            << bpmf.HanyuPinyinString(true, true) << " "
            << (*i).first << " "
            << (inBig5 ? "big5" : "ext")
            << endl;
    }
    
    
    delete b1;
    delete b2;
    
    return 0;
}
