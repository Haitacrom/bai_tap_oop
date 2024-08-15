#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class CanBo {
protected:
    string hoTen;
    int tuoi;
    string gioiTinh;
    string diaChi;

public:
    CanBo(string hoTen = "", int tuoi = 0, string gioiTinh = "", string diaChi = "")
        : hoTen(hoTen), tuoi(tuoi), gioiTinh(gioiTinh), diaChi(diaChi) {}
    string getHoTen() const { return hoTen; }
    void setHoTen(const string& hoTen) { this->hoTen = hoTen; }

    int getTuoi() const { return tuoi; }
    void setTuoi(int tuoi) { this->tuoi = tuoi; }

    string getGioiTinh() const { return gioiTinh; }
    void setGioiTinh(const string& gioiTinh) { this->gioiTinh = gioiTinh; }

    string getDiaChi() const { return diaChi; }
    void setDiaChi(const string& diaChi) { this->diaChi = diaChi; }

    virtual void print() const {
        cout << "Họ tên: " << hoTen << ", Tuổi: " << tuoi << ", Giới tính: " << gioiTinh << ", Địa chỉ: " << diaChi;
    }

    virtual ~CanBo() {}
};

class CongNhan : public CanBo {
private:
    int bac;

public:
    CongNhan(string hoTen = "", int tuoi = 0, string gioiTinh = "", string diaChi = "", int bac = 1)
        : CanBo(hoTen, tuoi, gioiTinh, diaChi), bac(bac) {}

    int getBac() const { return bac; }
    void setBac(int bac) { this->bac = bac; }

    void print() const override {
        CanBo::print();
        cout << ", Bậc: " << bac << endl;
    }
};

class KySu : public CanBo {
private:
    string nganhDaoTao;

public:
    KySu(string hoTen = "", int tuoi = 0, string gioiTinh = "", string diaChi = "", string nganhDaoTao = "")
        : CanBo(hoTen, tuoi, gioiTinh, diaChi), nganhDaoTao(nganhDaoTao) {}

    string getNganhDaoTao() const { return nganhDaoTao; }
    void setNganhDaoTao(const string& nganhDaoTao) { this->nganhDaoTao = nganhDaoTao; }

    void print() const override {
        CanBo::print();
        cout << ", Ngành đào tạo: " << nganhDaoTao << endl;
    }
};

class NhanVien : public CanBo {
private:
    string congViec;

public:
    NhanVien(string hoTen = "", int tuoi = 0, string gioiTinh = "", string diaChi = "", string congViec = "")
        : CanBo(hoTen, tuoi, gioiTinh, diaChi), congViec(congViec) {}

    string getCongViec() const { return congViec; }
    void setCongViec(const string& congViec) { this->congViec = congViec; }

    void print() const override {
        CanBo::print();
        cout << ", Công việc: " << congViec << endl;
    }
};

class QLCB {
private:
    vector<CanBo*> danhSachCanBo;

public:
    ~QLCB() {
        for (CanBo* canBo : danhSachCanBo) {
            delete canBo;
        }
    }

    void themCanBo() {
        int loaiCanBo;
        cout << "Nhập loại cán bộ (1. Công nhân, 2. Kỹ sư, 3. Nhân viên): ";
        cin >> loaiCanBo;
        cin.ignore();

        string hoTen, gioiTinh, diaChi;
        int tuoi;
        cout << "Nhập họ tên: ";
        getline(cin, hoTen);
        cout << "Nhập tuổi: ";
        cin >> tuoi;
        cin.ignore();
        cout << "Nhập giới tính (Nam/Nu/Khac): ";
        getline(cin, gioiTinh);
        cout << "Nhập địa chỉ: ";
        getline(cin, diaChi);
        string nganhDaoTao;
        string congViec;
        int bac;
        CanBo* canBo = nullptr;
        switch (loaiCanBo) {
        case 1:
            cout << "Nhập bậc: ";
            cin >> bac;
            cin.ignore();
            canBo = new CongNhan(hoTen, tuoi, gioiTinh, diaChi, bac);
            break;
        case 2:
            cout << "Nhập ngành đào tạo: ";
            getline(cin, nganhDaoTao);
            canBo = new KySu(hoTen, tuoi, gioiTinh, diaChi, nganhDaoTao);
            break;
        case 3:
            cout << "Nhập công việc: ";
            getline(cin, congViec);
            canBo = new NhanVien(hoTen, tuoi, gioiTinh, diaChi, congViec);
            break;
        default:
            cout << "Loại cán bộ không hợp lệ!" << endl;
            return;
        }
        danhSachCanBo.push_back(canBo);
        cout << "Thêm cán bộ thành công!" << endl;
    }

    void timKiemCanBo() const {
        string hoTen;
        cout << "Nhập họ tên cán bộ cần tìm: ";
        getline(cin, hoTen);

        bool found = false;
        for (const CanBo* canBo : danhSachCanBo) {
            if (canBo->getHoTen() == hoTen) {
                canBo->print();
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Không tìm thấy cán bộ với họ tên này!" << endl;
        }
    }

    void hienThiDanhSachCanBo() const {
        if (danhSachCanBo.empty()) {
            cout << "Danh sách cán bộ trống!" << endl;
        }
        else {
            for (const CanBo* canBo : danhSachCanBo) {
                canBo->print();
            }
        }
    }

    void menu() {
        int luaChon;
        do {
            cout << "\n--- Quản lý cán bộ ---" << endl;
            cout << "1. Thêm mới cán bộ" << endl;
            cout << "2. Tìm kiếm cán bộ theo họ tên" << endl;
            cout << "3. Hiển thị danh sách cán bộ" << endl;
            cout << "4. Thoát" << endl;
            cout << "Nhập lựa chọn của bạn: ";
            cin >> luaChon;
            cin.ignore();
            switch (luaChon) {
            case 1:
                themCanBo();
                break;
            case 2:
                timKiemCanBo();
                break;
            case 3:
                hienThiDanhSachCanBo();
                break;
            case 4:
                cout << "Thoát chương trình." << endl;
                break;
            default:
                cout << "Lựa chọn không hợp lệ. Vui lòng chọn lại." << endl;
                break;
            }
        } while (luaChon != 4);
    }
};

int main() {
    QLCB qlcb;
    qlcb.menu();
    return 0;
}