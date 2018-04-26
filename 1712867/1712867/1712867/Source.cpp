﻿#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <string.h>
#include <conio.h>
#define N 10

//KHAI BÁO CẤU TRÚC SINH VIÊN
struct sinhvien{
	wchar_t MSSV[10];
	wchar_t HovaTen[30];
	wchar_t Khoa[30];
	wchar_t NienKhoa[5];
	wchar_t Email[20];
	wchar_t Ngaysinh[20];
	wchar_t Hinh[20];
	wchar_t MoTa[1000];
	wchar_t Sothich[1000];
};
typedef struct sinhvien SINHVIEN;

//ĐỌC FILE GIOITHIEU.CSV
void DocFileCSV(FILE *FileIn, SINHVIEN *&sv)
{
	for (int i = 0; i < N; i++)
	{
		//ĐỌC DỮ LIỆU SINH VIÊN THEO DÂU ','
		fwscanf(FileIn, L"%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,]", &sv[i].MSSV, &sv[i].HovaTen, &sv[i].Khoa, &sv[i].NienKhoa, &sv[i].Email, &sv[i].Ngaysinh, &sv[i].Hinh);

		//ĐỌC DỮ LIỆU SINHVIÊN.MÔTẢ 
		//CÓ 2 TRƯỜNG HỢP ( 1.CHUỖI KHÔNG CÓ DẤU ',' , 2.CHUỖI CÓ DẤU ',')
		fseek(FileIn, 1, 1);
		wchar_t KiemTra;
		KiemTra = fgetwc(FileIn); //LẤY KÍ TỰ ĐẦU TIÊN SAU DẤU ','

		if (KiemTra == '"')  //TRƯỜNG HỢP CÓ DẤU ','
		{
			fwscanf(FileIn, L"%[^\"]", &sv[i].MoTa);
			fseek(FileIn, 1, 1);
		}
		else //TRƯỜNG HỢP KHÔNG CÓ DẤU ','
		{
			fseek(FileIn, -1, 1);
			fwscanf(FileIn, L"%[^,]", &sv[i].MoTa);
		}

		fseek(FileIn, 1, 1);

		//ĐỌC CÁC KÍ TỰ CÒN LẠI TRONG DÒNG VÀ GÁN VÀO SINHVIÊN.SỞTHÍCH
		fgetws(sv[i].Sothich, 1000, FileIn);
	}
}

// HÀM XỬ LÝ CHUỖI CÓ DẤU " "
void XuLyChuoi(wchar_t ChuoiCanXuLy[])
{
	int ChieuDaiChuoi = wcslen(ChuoiCanXuLy);
	if (ChuoiCanXuLy[0] == '"')
	{
		for (int i = 0; i < ChieuDaiChuoi; i++)
		{
			ChuoiCanXuLy[i] = ChuoiCanXuLy[i + 1];
		}
		ChieuDaiChuoi -= 1;
		if (ChuoiCanXuLy[ChieuDaiChuoi - 2] == '"')
		{
			ChuoiCanXuLy[ChieuDaiChuoi - 2] = ChuoiCanXuLy[ChieuDaiChuoi - 1];
			ChuoiCanXuLy[ChieuDaiChuoi - 1] = ChuoiCanXuLy[ChieuDaiChuoi];
			ChieuDaiChuoi -= 1;
		}
		else
		{
			ChuoiCanXuLy[ChieuDaiChuoi - 1] = ChuoiCanXuLy[ChieuDaiChuoi];
			ChieuDaiChuoi -= 1;
		}
	}
}

//HÀM CHÈN DỮ LIỆU SINH VIÊN VÀO HTML
void ChenDuLieu(wchar_t *ChuoiCha, wchar_t *ChuoiCon, int ViTriChen)
{
	int DoDaiChuoiCha = wcslen(ChuoiCha);
	int DoDaiChuoiCon = wcslen(ChuoiCon);
	wchar_t *temp;
	if (ViTriChen > DoDaiChuoiCha)
	{
		ViTriChen = DoDaiChuoiCha;
	}
	if (ViTriChen < DoDaiChuoiCha)
	{
		temp = new wchar_t[DoDaiChuoiCha - ViTriChen + 1];
		wcscpy(temp, ChuoiCha + ViTriChen);
		wcscpy(ChuoiCha + ViTriChen, ChuoiCon);
		wcscpy(ChuoiCha + ViTriChen + DoDaiChuoiCon, temp);
		delete[] temp;
	}
	else wcscpy(ChuoiCha + ViTriChen, ChuoiCon);
}


//HÀM TẠO TÊN FILE.HTML
void TaoTenFile(wchar_t* MSSV, wchar_t TenFile[])
{
	wchar_t DuoiFile[] = L".html";
	wcscat(TenFile, MSSV);
	wcscat(TenFile, DuoiFile);
}


//HÀM XULY DÙNG ĐỂ NỘI DUNG TỪ FILE HTML.TXT ĐỒNG THỜI GHI DỮ LIỆU VÀO FILE .HTML
void XuLy(FILE* FileHTML, SINHVIEN *sv)
{

	//KHAI BÁO CÁC DÒNG DÙNG ĐỂ CHÈN THÔNG TIN SINH VIÊN
	wchar_t Title[] = L"<title>HCMUS - ";
	int ChieuDai1 = wcslen(Title);

	wchar_t Personal_Fullname[] = L"<span class=\"Personal_FullName\"> ";
	int ChieuDai2 = wcslen(Personal_Fullname);

	wchar_t Personal_Department[] = L"<div class=\"Personal_Department\">KHOA ";
	int ChieuDai3 = wcslen(Personal_Department);

	wchar_t Email[] = L"<div class=\"Personal_Phone\">Email: ";
	int ChieuDai4 = wcslen(Email);

	wchar_t Personal_Image[] = L"<div class=\"Personal_HinhcanhanKhung\"><img src=\"Images/";
	int ChieuDai5 = wcslen(Personal_Image);

	wchar_t HovaTen[] = L"<li>Họ và tên: ";
	int ChieuDai6 = wcslen(HovaTen);

	wchar_t MSSV[] = L"<li>MSSV: ";
	int ChieuDai7 = wcslen(MSSV);

	wchar_t SinhVienKhoa[] = L"<li>Sinh viên khoa ";
	int ChieuDai8 = wcslen(SinhVienKhoa);

	wchar_t Khoa[] = L"<li>Khóa: ";
	int ChieuDai9 = wcslen(Khoa);

	wchar_t Email_2[] = L"<li>Email: ";
	int ChieuDai10 = wcslen(Email_2);

	wchar_t Ngaysinh[] = L"<li>Ngày sinh: ";
	int ChieuDai11 = wcslen(Ngaysinh);

	wchar_t SoThich[] = L"<ul class=\"TextInList\"><li>";
	int ChieuDai12 = wcslen(SoThich);

	wchar_t Mota[] = L"<div class=\"Description\">";
	int ChieuDai13 = wcslen(Mota);

	wchar_t SinhVienThucHien[] = L"TH2012/03</br>";
	int ChieuDai14 = wcslen(SinhVienThucHien);

	//GHI DỮ LIỆU VÀO FILE.HTML
	for (int i = 0; i < N; i++)
	{
		FILE* FileOut;
		wchar_t TenFile[25]=L"Website\\";
		TaoTenFile(sv[i].MSSV, TenFile);
		FileOut = _wfopen(TenFile, L"w,ccs=UTF-8");
		wchar_t s[1000]; //CHUỖI DÙNG ĐỂ ĐỌC TỪNG DÒNG TRONG FILE HTML.TXT
		while (!feof(FileHTML))
		{
			fgetws(s, 1000, FileHTML);
			if (wcsstr(s, Title) != NULL)
			{
				ChenDuLieu(s, sv[i].HovaTen, ChieuDai1);
				fputws(s, FileOut);
				continue; //DÙNG ĐỂ BỎ QUA CÁC DÒNG BÊN DƯỚI VÀ THỰC HIỆN TIẾP VÒNG LẶP
			}
			if (wcsstr(s, Personal_Fullname) != NULL)
			{
				wchar_t a[] = L" - ";
				int ChieuDaiTen = wcslen(sv[i].HovaTen);
				ChenDuLieu(s, sv[i].HovaTen, ChieuDai2);
				ChenDuLieu(s, a, ChieuDai2 + ChieuDaiTen);
				ChenDuLieu(s, sv[i].MSSV, ChieuDai2 + ChieuDaiTen + 3);
				fputws(s, FileOut);
				continue;
			}
			if (wcsstr(s, Personal_Department) != NULL)
			{
				_wcsupr(sv[i].Khoa);
				ChenDuLieu(s, sv[i].Khoa, ChieuDai3);
				fputws(s, FileOut);
				continue;
			}
			if (wcsstr(s, Email) != NULL)
			{
				ChenDuLieu(s, sv[i].Email, ChieuDai4);
				fputws(s, FileOut);
				continue;
			}
			if (wcsstr(s, Personal_Image) != NULL)
			{
				ChenDuLieu(s, sv[i].Hinh, ChieuDai5);
				fputws(s, FileOut);
				continue;
			}
			if (wcsstr(s, HovaTen) != NULL)
			{
				ChenDuLieu(s, sv[i].HovaTen, ChieuDai6);
				fputws(s, FileOut);
				continue;
			}if (wcsstr(s, MSSV) != NULL)
			{
				ChenDuLieu(s, sv[i].MSSV, ChieuDai7);
				fputws(s, FileOut);
				continue;
			}
			if (wcsstr(s, SinhVienKhoa) != NULL)
			{
				_wcslwr(sv[i].Khoa);
				ChenDuLieu(s, sv[i].Khoa, ChieuDai8);
				fputws(s, FileOut);
				continue;
			}
			if (wcsstr(s, Khoa) != NULL)
			{
				ChenDuLieu(s, sv[i].NienKhoa, ChieuDai9);
				fputws(s, FileOut);
				continue;
			}
			if (wcsstr(s, Email_2) != NULL)
			{
				ChenDuLieu(s, sv[i].Email, ChieuDai10);
				fputws(s, FileOut);
				continue;
			}
			if (wcsstr(s, Ngaysinh) != NULL)
			{
				ChenDuLieu(s, sv[i].Ngaysinh, ChieuDai11);
				fputws(s, FileOut);
				continue;
			}
			if (wcsstr(s, SoThich) != NULL)
			{
				XuLyChuoi(sv[i].Sothich);
				ChenDuLieu(s, sv[i].Sothich, ChieuDai12);
				fputws(s, FileOut);
				continue;
			}
			if (wcsstr(s, Mota) != NULL)
			{
				XuLyChuoi(sv[i].MoTa);
				ChenDuLieu(s, sv[i].MoTa, ChieuDai13);
				fputws(s, FileOut);
				continue;
			}
			if (wcsstr(s, SinhVienThucHien) != NULL)
			{
				wchar_t MaSoSinhVien[] = L"1712867 - ";
				int ChieuDaiMaSo = wcslen(MaSoSinhVien);

				wchar_t Ten[] = L"Âu Dương Gia Tuấn";

				ChenDuLieu(s, MaSoSinhVien, ChieuDai6);
				ChenDuLieu(s, Ten, ChieuDai6 + ChieuDaiMaSo);
				fputws(s, FileOut);
				continue;
			}
			fputws(s, FileOut);
		}
		fclose(FileOut);
		rewind(FileHTML); //DỜI CON TRỎ VỀ VỊ TRÍ ĐẦU FILE
	}
}


int wmain(int argc, wchar_t* argv[])
{
	SINHVIEN *sv = new SINHVIEN[N];
	FILE *FileIn, *FileHTML;

	//MỞ FILE GIOITHIEU.CSV
	FileIn = _wfopen(L"gioithieu.csv", L"r,ccs=UTF-8");
	if (!FileIn)
	{
		wprintf(L"Khong the mo file.\n");
	}
	else
	{
		DocFileCSV(FileIn, sv);
	}

	//MỞ FILE HTML.TXT 
	FileHTML = _wfopen(L"HTML.txt", L"r,ccs=UTF-8");
	if (!FileHTML)
	{
		wprintf(L"Khong the mo file.\n");
	}
	else
	{
		XuLy(FileHTML, sv);
	}
	fclose(FileIn);
	fclose(FileHTML);
	delete[] sv;
	_getch();
}