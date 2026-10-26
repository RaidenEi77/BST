// THUC HANH: CAY NHI PHAN TIM KIEM (BST) - QUAN LY DANH MUC SAN PHAM
// Khoa so sanh: maSP. Bien dich: g++ -std=c++11 -Wall -Wextra -o bst src/main.cpp
#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <new>
using namespace std;

const int TEN_MAX = 49;

struct Product {
    int maSP;
    char tenSP[TEN_MAX + 1];
    int soLuong;
    double donGia;
};

struct Node {
    Product data;
    Node* left;
    Node* right;
};

enum KetQuaChen { CHEN_OK, CHEN_TRUNG, CHEN_SAI, CHEN_HET_BO_NHO };

const Product MAU[7] = {
    {50, "But bi",     120,  5000},
    {30, "Vo o ly",     80, 12000},
    {70, "Bia ho so",   35, 15000},
    {20, "Thuoc ke",    40,  8000},
    {40, "Tay",         65,  4000},
    {60, "So tay",      25, 25000},
    {80, "But chi",    110,  3000}
};

// ---------------------------------------------------------------- Kiem tra
// Tra ve NULL neu hop le, nguoc lai tra ve noi dung loi.
const char* loiDuLieu(const Product& sp) {
    if (sp.maSP <= 0)        return "Ma san pham phai > 0";
    if (sp.tenSP[0] == '\0') return "Ten san pham khong duoc rong";
    if (sp.soLuong < 0)      return "So luong phai >= 0";
    if (sp.donGia < 0)       return "Don gia phai >= 0";
    return NULL;
}

// ------------------------------------------------------------- Thao tac BST
Node* khoiTaoNode(const Product& sp) {
    Node* n = new(nothrow) Node;
    if (n == NULL) return NULL;
    n->data = sp;
    n->left = n->right = NULL;
    return n;
}

// F1: dung con tro cap 2 de khong phai xu ly rieng cay rong.
KetQuaChen themSanPham(Node*& root, const Product& sp) {
    if (loiDuLieu(sp) != NULL) return CHEN_SAI;
    Node** cur = &root;
    while (*cur != NULL) {
        if (sp.maSP == (*cur)->data.maSP) return CHEN_TRUNG;
        cur = (sp.maSP < (*cur)->data.maSP) ? &(*cur)->left : &(*cur)->right;
    }
    Node* n = khoiTaoNode(sp);
    if (n == NULL) return CHEN_HET_BO_NHO;
    *cur = n;
    return CHEN_OK;
}

// F2
Node* timSanPham(Node* root, int ma) {
    while (root != NULL && root->data.maSP != ma)
        root = (ma < root->data.maSP) ? root->left : root->right;
    return root;
}

Node* nutNhoNhat(Node* n) {
    while (n != NULL && n->left != NULL) n = n->left;
    return n;
}

// F3: xoa du 3 truong hop; nut hai con dung nut ke tiep trung thu tu.
Node* xoaNode(Node* root, int ma, bool& daXoa) {
    if (root == NULL) return NULL;
    if (ma < root->data.maSP) {
        root->left = xoaNode(root->left, ma, daXoa);
    } else if (ma > root->data.maSP) {
        root->right = xoaNode(root->right, ma, daXoa);
    } else {
        daXoa = true;
        if (root->left == NULL) {            // la hoac chi co con phai
            Node* r = root->right;
            delete root;
            return r;
        }
        if (root->right == NULL) {           // chi co con trai
            Node* l = root->left;
            delete root;
            return l;
        }
        Node* ke = nutNhoNhat(root->right);  // hai con: successor
        root->data = ke->data;
        bool tam = false;
        root->right = xoaNode(root->right, ke->data.maSP, tam);
    }
    return root;
}

int demNut(const Node* root) {
    return root == NULL ? 0 : 1 + demNut(root->left) + demNut(root->right);
}

int chieuCao(const Node* root) {
    if (root == NULL) return 0;
    int t = chieuCao(root->left), p = chieuCao(root->right);
    return 1 + (t > p ? t : p);
}

void giaiPhong(Node*& root) {
    if (root == NULL) return;
    giaiPhong(root->left);
    giaiPhong(root->right);
    delete root;
    root = NULL;
}

bool laBST(const Node* n, long long lo, long long hi) {
    if (n == NULL) return true;
    if (n->data.maSP <= lo || n->data.maSP >= hi) return false;
    return laBST(n->left, lo, n->data.maSP) && laBST(n->right, n->data.maSP, hi);
}

// ------------------------------------------------------------- Hien thi
void inTieuDe() {
    cout << left << setw(10) << "Ma SP" << setw(24) << "Ten san pham"
         << setw(11) << "So luong" << "Don gia\n";
    cout << "-----------------------------------------------------------\n";
}

void inSanPham(const Product& sp) {
    cout << left << setw(10) << sp.maSP << setw(24) << sp.tenSP
         << setw(11) << sp.soLuong << fixed << setprecision(0) << sp.donGia << "\n";
}

// F4: duyet LNR
void duyetLNR(const Node* root) {
    if (root == NULL) return;
    duyetLNR(root->left);
    inSanPham(root->data);
    duyetLNR(root->right);
}

void chuoiLNR(const Node* root, string& out) {
    if (root == NULL) return;
    chuoiLNR(root->left, out);
    if (!out.empty()) out += " ";
    out += to_string(root->data.maSP);
    chuoiLNR(root->right, out);
}

string lnr(const Node* root) {
    string s;
    chuoiLNR(root, s);
    return s;
}

// Ve cay xoay ngang: goc ben trai, nhanh phai o tren.
void veCay(const Node* n, int sau) {
    if (n == NULL) return;
    veCay(n->right, sau + 1);
    cout << string(sau * 6, ' ') << n->data.maSP << "\n";
    veCay(n->left, sau + 1);
}

// ------------------------------------------------------------- Nhap lieu
bool docDong(const char* loiNhac, string& s) {
    cout << loiNhac;
    return static_cast<bool>(getline(cin, s));
}

bool docInt(const char* loiNhac, int& x) {
    string s;
    while (docDong(loiNhac, s)) {
        char* end;
        long v = strtol(s.c_str(), &end, 10);
        if (!s.empty() && *end == '\0' && v >= -2000000000L && v <= 2000000000L) {
            x = static_cast<int>(v);
            return true;
        }
        cout << "  Khong phai so nguyen hop le, nhap lai.\n";
    }
    return false;
}

bool docDouble(const char* loiNhac, double& x) {
    string s;
    while (docDong(loiNhac, s)) {
        char* end;
        double v = strtod(s.c_str(), &end);
        if (!s.empty() && *end == '\0') { x = v; return true; }
        cout << "  Khong phai so hop le, nhap lai.\n";
    }
    return false;
}

void baoKetQuaChen(KetQuaChen kq, const Product& sp) {
    switch (kq) {
        case CHEN_OK:          cout << "Da them san pham " << sp.maSP << " - " << sp.tenSP << ".\n"; break;
        case CHEN_TRUNG:       cout << "Ma san pham da ton tai\n"; break;
        case CHEN_SAI:         cout << "Du lieu khong hop le: " << loiDuLieu(sp) << "\n"; break;
        case CHEN_HET_BO_NHO:  cout << "Khong du bo nho de them san pham!\n"; break;
    }
}

void chucNangThem(Node*& root) {
    Product sp;
    memset(&sp, 0, sizeof sp);
    string ten;
    if (!docInt("Nhap ma san pham: ", sp.maSP)) return;
    if (!docDong("Nhap ten san pham (toi da 49 ky tu): ", ten)) return;
    if (!docInt("Nhap so luong: ", sp.soLuong)) return;
    if (!docDouble("Nhap don gia: ", sp.donGia)) return;
    if (ten.size() > static_cast<size_t>(TEN_MAX)) {
        cout << "Du lieu khong hop le: Ten dai qua 49 ky tu\n";
        return;
    }
    strcpy(sp.tenSP, ten.c_str());
    baoKetQuaChen(themSanPham(root, sp), sp);
}

void chucNangTim(Node* root) {
    int ma;
    if (!docInt("Nhap ma can tim: ", ma)) return;
    Node* n = timSanPham(root, ma);
    if (n == NULL) { cout << "Khong tim thay san pham\n"; return; }
    inTieuDe();
    inSanPham(n->data);
}

void chucNangXoa(Node*& root) {
    int ma;
    bool daXoa = false;
    if (!docInt("Nhap ma can xoa: ", ma)) return;
    root = xoaNode(root, ma, daXoa);
    if (daXoa) cout << "Da xoa san pham " << ma << ".\n";
    else       cout << "Khong tim thay san pham\n";
}

void napMau(Node*& root) {
    giaiPhong(root);
    for (int i = 0; i < 7; ++i) themSanPham(root, MAU[i]);
    cout << "Da nap " << demNut(root) << " san pham mau (dung thu tu chen).\n";
}

// ------------------------------------------------------------- Kiem thu tu dong
int dat = 0, truot = 0;

void kiemTra(const char* id, const char* mucTieu, const char* dauVao,
             const string& kyVong, const string& thucTe) {
    bool ok = (kyVong == thucTe);
    if (ok) ++dat; else ++truot;
    cout << "[" << id << "] " << (ok ? "PASS" : "FAIL") << "\n"
         << "    Muc tieu : " << mucTieu << "\n"
         << "    Dau vao  : " << dauVao << "\n"
         << "    Ky vong  : " << kyVong << "\n"
         << "    Thuc te  : " << thucTe << "\n";
}

Node* taoCayMau() {
    Node* t = NULL;
    for (int i = 0; i < 7; ++i) themSanPham(t, MAU[i]);
    return t;
}

Node* taoCayTuMa(const int* ds, int n) {
    Node* t = NULL;
    for (int i = 0; i < n; ++i) {
        Product sp = { ds[i], "SP", 1, 1000.0 };
        themSanPham(t, sp);
    }
    return t;
}


string so(int x) { return to_string(x); }
string cb(bool b, const char* y, const char* n) { return b ? y : n; }

int chayKiemThu() {
    dat = truot = 0;
    cout << "=== KIEM THU TU DONG - BST QUAN LY SAN PHAM ===\n\n";
    Node* t = NULL;
    bool daXoa;

    // T01
    kiemTra("T01", "Cay rong", "Chua chen gi", "nut=0, cao=0, tim 50=khong",
            "nut=" + so(demNut(t)) + ", cao=" + so(chieuCao(t)) + ", tim 50=" +
            cb(timSanPham(t, 50) != NULL, "co", "khong"));

    // T02, T03
    t = taoCayMau();
    kiemTra("T02", "Duyet LNR sau khi nap 7 san pham mau", "Chen 50,30,70,20,40,60,80",
            "20 30 40 50 60 70 80", lnr(t));
    kiemTra("T03", "Dem nut va chieu cao", "Cay mau", "nut=7, cao=3",
            "nut=" + so(demNut(t)) + ", cao=" + so(chieuCao(t)));

    // T04
    {
        Node* n = timSanPham(t, 60);
        string tt = n ? string(n->data.tenSP) + "|" + so(n->data.soLuong) + "|" +
                        so(static_cast<int>(n->data.donGia))
                      : "khong tim thay";
        kiemTra("T04", "Tim ma ton tai", "Tim 60", "So tay|25|25000", tt);
    }
    // T05
    kiemTra("T05", "Tim ma khong ton tai", "Tim 99", "khong tim thay",
            cb(timSanPham(t, 99) != NULL, "co", "khong tim thay"));

    // T06
    {
        Product trung = {50, "But bi (lan 2)", 1, 1};
        KetQuaChen kq = themSanPham(t, trung);
        kiemTra("T06", "Chen trung ma", "Chen lai ma 50", "TRUNG, nut=7, ten giu nguyen=dung",
                string(kq == CHEN_TRUNG ? "TRUNG" : "khac") + ", nut=" + so(demNut(t)) +
                ", ten giu nguyen=" +
                cb(strcmp(timSanPham(t, 50)->data.tenSP, "But bi") == 0, "dung", "sai"));
    }
    // T07
    {
        Product xau[5] = { {0, "A", 1, 1}, {-5, "A", 1, 1}, {99, "A", -1, 1},
                           {99, "A", 1, -1}, {99, "", 1, 1} };
        int tuChoi = 0;
        for (int i = 0; i < 5; ++i)
            if (themSanPham(t, xau[i]) == CHEN_SAI) ++tuChoi;
        kiemTra("T07", "Du lieu khong hop le bi tu choi",
                "maSP=0; maSP=-5; soLuong=-1; donGia=-1; ten rong",
                "tu choi=5, nut=7", "tu choi=" + so(tuChoi) + ", nut=" + so(demNut(t)));
    }
    giaiPhong(t);

    // T08
    t = taoCayMau();
    {
        Product bien;
        memset(&bien, 0, sizeof bien);
        bien.maSP = 90;
        memset(bien.tenSP, 'A', TEN_MAX);
        bien.tenSP[TEN_MAX] = '\0';
        KetQuaChen kq = themSanPham(t, bien);
        kiemTra("T08", "Bien: ten dai dung 49 ky tu, soLuong=0, donGia=0", "Chen ma 90",
                "OK, nut=8, cao=4",
                string(kq == CHEN_OK ? "OK" : "loi") + ", nut=" + so(demNut(t)) +
                ", cao=" + so(chieuCao(t)));
    }
    giaiPhong(t);

    // T09, T10
    t = taoCayMau(); daXoa = false;
    t = xoaNode(t, 20, daXoa);
    kiemTra("T09", "Xoa nut la", "Xoa 20 tren cay mau",
            "daXoa=1; LNR=30 40 50 60 70 80; nut=6",
            "daXoa=" + so(daXoa) + "; LNR=" + lnr(t) + "; nut=" + so(demNut(t)));
    daXoa = false;
    t = xoaNode(t, 30, daXoa);
    kiemTra("T10", "Xoa nut mot con (con phai 40)", "Sau khi xoa 20, xoa 30",
            "daXoa=1; LNR=40 50 60 70 80; con trai goc=40",
            "daXoa=" + so(daXoa) + "; LNR=" + lnr(t) + "; con trai goc=" +
            so(t->left ? t->left->data.maSP : -1));
    giaiPhong(t);

    // T11
    t = taoCayMau(); daXoa = false;
    t = xoaNode(t, 70, daXoa);
    kiemTra("T11", "Xoa nut hai con (successor = 80)", "Xoa 70 tren cay ban dau",
            "daXoa=1; LNR=20 30 40 50 60 80; con phai goc=80; con 70=khong",
            "daXoa=" + so(daXoa) + "; LNR=" + lnr(t) + "; con phai goc=" +
            so(t->right ? t->right->data.maSP : -1) + "; con 70=" +
            cb(timSanPham(t, 70) != NULL, "co", "khong"));
    giaiPhong(t);

    // T12
    t = taoCayMau(); daXoa = false;
    t = xoaNode(t, 50, daXoa);
    kiemTra("T12", "Xoa nut goc co hai con (successor = 60)", "Xoa 50 tren cay ban dau",
            "daXoa=1; goc=60; LNR=20 30 40 60 70 80; laBST=dung",
            "daXoa=" + so(daXoa) + "; goc=" + so(t ? t->data.maSP : -1) + "; LNR=" +
            lnr(t) + "; laBST=" + cb(laBST(t, -(1LL << 40), 1LL << 40), "dung", "sai"));
    giaiPhong(t);

    // T13
    t = taoCayMau(); daXoa = false;
    t = xoaNode(t, 99, daXoa);
    kiemTra("T13", "Xoa ma khong ton tai", "Xoa 99", "daXoa=0; nut=7",
            "daXoa=" + so(daXoa) + "; nut=" + so(demNut(t)));
    giaiPhong(t);

    // T14
    t = NULL; daXoa = false;
    t = xoaNode(t, 10, daXoa);
    kiemTra("T14", "Xoa tren cay rong", "Xoa 10", "daXoa=0; cay rong",
            "daXoa=" + so(daXoa) + "; cay " + cb(t == NULL, "rong", "khong rong"));

    // T15
    {
        int tang[7] = {10, 20, 30, 40, 50, 60, 70};
        int canDoi[7] = {40, 20, 60, 10, 30, 50, 70};
        Node* a = taoCayTuMa(tang, 7);
        Node* b = taoCayTuMa(canDoi, 7);
        kiemTra("T15", "So sanh cay suy bien va cay can doi (7 nut)",
                "Chen 10..70 tang dan; chen 40,20,60,10,30,50,70",
                "suy bien: nut=7 cao=7 | can doi: nut=7 cao=3",
                "suy bien: nut=" + so(demNut(a)) + " cao=" + so(chieuCao(a)) +
                " | can doi: nut=" + so(demNut(b)) + " cao=" + so(chieuCao(b)));
        giaiPhong(a);
        giaiPhong(b);
    }

    // T16
    t = taoCayMau();
    {
        int thuTu[4] = {20, 30, 70, 50};
        for (int i = 0; i < 4; ++i) { daXoa = false; t = xoaNode(t, thuTu[i], daXoa); }
    }
    kiemTra("T16", "Chuoi nhieu phep xoa van giu bat bien BST", "Xoa lan luot 20,30,70,50",
            "laBST=dung; LNR=40 60 80; nut=3",
            "laBST=" + cb(laBST(t, -(1LL << 40), 1LL << 40), "dung", "sai") + "; LNR=" +
            lnr(t) + "; nut=" + so(demNut(t)));

    // T17
    giaiPhong(t);
    kiemTra("T17", "Giai phong toan bo cay", "giaiPhong()", "goc=NULL, nut=0",
            string("goc=") + (t == NULL ? "NULL" : "khac NULL") + ", nut=" + so(demNut(t)));

    cout << "\n=== TONG KET: " << dat << " PASS, " << truot << " FAIL (tong "
         << dat + truot << " ca) ===\n";
    return truot == 0 ? 0 : 1;
}

// ------------------------------------------------------------- main
int main(int argc, char** argv) {
    if (argc > 1 && strcmp(argv[1], "--test") == 0) return chayKiemThu();

    Node* root = NULL;
    int chon = -1;

    do {
        cout << "\n========== QUAN LY SAN PHAM BST ==========\n"
             << "1. Them san pham\n"
             << "2. Tim kiem san pham theo ma\n"
             << "3. Xoa san pham theo ma\n"
             << "4. In danh sach tang dan theo ma (LNR)\n"
             << "5. Dem so nut va chieu cao cay\n"
             << "6. Nap 7 san pham mau\n"
             << "7. Hien thi hinh dang cay\n"
             << "8. Chay kiem thu tu dong\n"
             << "0. Thoat\n";
        if (!docInt("Nhap lua chon: ", chon)) break;   // het du lieu vao -> thoat

        switch (chon) {
            case 1: chucNangThem(root); break;
            case 2: chucNangTim(root);  break;
            case 3: chucNangXoa(root);  break;
            case 4:
                if (root == NULL) cout << "Danh sach san pham rong!\n";
                else { inTieuDe(); duyetLNR(root); }
                break;
            case 5:
                cout << "So nut = " << demNut(root) << "; chieu cao = " << chieuCao(root) << "\n";
                break;
            case 6: napMau(root); break;
            case 7:
                if (root == NULL) cout << "Cay rong!\n";
                else { cout << "(goc ben trai, nhanh phai o tren)\n"; veCay(root, 0); }
                break;
            case 8: chayKiemThu(); break;
            case 0: break;
            default: cout << "Lua chon khong hop le!\n";
        }
    } while (chon != 0);

    giaiPhong(root);   // F7
    cout << "Da giai phong bo nho. Ket thuc chuong trinh!\n";
    return 0;
}
