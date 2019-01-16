#include "Card.h"

// Function: viewCard ======================================================= //
void Card::viewCard(int state, bool end) {
    if (state == 0) cout << char(201) << char(205) << char(205) << char(205) <<
                            char(205) << char(205) << char(187);
    if (state == 1) {
        if (rank != "10") cout << char(186) << rank << "   " <<
                                  suit << char(186);
        else cout << char(186) << rank << "  " << suit << char(186);
    }
    if (state == 2) cout << char(186) << "     " << char(186);
    if (state == 3) cout << char(186) << "     " << char(186);
    if (state == 4) cout << char(186) << "     " << char(186);
    if (state == 5) {
        if (rank != "10") cout << char(186) << suit << "   " <<
                                  rank << char(186);
        else cout << char(186) << suit << "  " << rank << char(186);
    }
    if (state == 6) cout << char(200) << char(205) << char(205) << char(205) <<
                            char(205) << char(205) << char(188);
    if (end) cout << endl;
}

// Constructor ============================================================== //
Card::Card() {}

// Destructor =============================================================== //
Card::~Card() {}