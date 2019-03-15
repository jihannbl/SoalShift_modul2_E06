# Soal Shift Modul 2 (Kelompok E6)

###### Nama Anggota :
1. Ifta Jihan Nabila (05111740000034)
2. Komang Yogananda MW (05111740000114)

**Penjelasan Soal Shift Modul 2 Sistem Operasi 2019:**
* [Soal 1](https://github.com/jihannbl/SoalShift_modul2_E06#soal-1)
* [Soal 2](https://github.com/jihannbl/SoalShift_modul2_E06#soal-2)
* [Soal 3](https://github.com/jihannbl/SoalShift_modul2_E06#soal-3)
* [Soal 4](https://github.com/jihannbl/SoalShift_modul2_E06#soal-4)
* [Soal 5](https://github.com/jihannbl/SoalShift_modul2_E06#soal-5)

## Soal 1
Elen mempunyai pekerjaan pada studio sebagai fotografer. Suatu hari ada seorang klien yang bernama Kusuma yang meminta untuk mengubah nama file yang memiliki ekstensi .png menjadi “[namafile]_grey.png”. Karena jumlah file yang diberikan Kusuma tidak manusiawi, maka Elen meminta bantuan kalian untuk membuat suatu program C yang dapat mengubah nama secara otomatis dan diletakkan pada direktori /home/[user]/modul2/gambar.

Catatan : Tidak boleh menggunakan crontab.

  
## Soal 2
Pada suatu hari Kusuma dicampakkan oleh Elen karena Elen dimenangkan oleh orang lain. Semua kenangan tentang Elen berada pada file bernama “elen.ku” pada direktori “hatiku”. Karena sedih berkepanjangan, tugas kalian sebagai teman Kusuma adalah membantunya untuk menghapus semua kenangan tentang Elen dengan membuat program C yang bisa mendeteksi owner dan group dan menghapus file “elen.ku” setiap 3 detik dengan syarat ketika owner dan grupnya menjadi “www-data”. Ternyata kamu memiliki kendala karena permission pada file “elen.ku”. Jadi, ubahlah permissionnya menjadi 777. Setelah kenangan tentang Elen terhapus, maka Kusuma bisa move on.

Catatan: Tidak boleh menggunakan crontab

**_Jawaban:_**

Menggunakan `<sys/stat.h>` header yang digunakan oleh **stat()** untuk mendapatkan informasi dari atribut pada structure.

```c
struct stat info;
stat("/home/jihan/hatiku/elen.ku", &info);
struct passwd *pwd = getpwuid(info.st_uid);
struct group  *grp = getgrgid(info.st_gid);
```

 - memanggil fungsi stat untuk menyimpan seluruh informasi pada file **elen.ku** yang disimpan pada atribut **info**
 - membuat variabel **pwd** **grp** untuk menyimpan informasi user dan group pada file
 - `st_uid` untuk mendapatkan user ID dari file
 - `st_gid` untuk mendapatkan group ID dari file
 
```c
if ( strcmp(pwd->pw_name, "www-data") == 0 && strcmp(grp->gr_name, "www-data") == 0)
{
  pid_t child = fork();
  int status = 0;
  if (child == 0)
  {
    char *argv[4] = {"chmod", "777", "/home/jihan/hatiku/elen.ku", NULL};
    execv("/bin/chmod", argv);
  }
  else
  {
        while((wait(&status)) > 0);
        remove("/home/jihan/hatiku/elen.ku");
  }
}
 ```
 
File **elen.ku** akan dihapus apabila owner dan group file tersebut yaitu "www-data", namun sebelum dihapus ubah permission pada file **elen.ku** menjadi **777**.

 - Pertama cek apakah owner dan group file pada file **elen.ku** adalah "www-data" dengan sintaks 
 ```c
 if ( strcmp(pwd->pw_name, "www-data") == 0 && strcmp(grp->gr_name, "www-data") == 0)
 ```
 - Gunakan **fork()**, jalankan child untuk mengganti file permission menjadi **777** menggunakan command **chmod**. Berikut ini sintaksnya
```c
char *argv[4] = {"chmod", "777", "/home/jihan/hatiku/elen.ku", NULL};
execv("/bin/chmod", argv);
```
 - Setelah child telah dieksekusi, maka parent akan menjalankan perintah untuk menghapus file **elen.ku**
 ```c
 while((wait(&status)) > 0);
 remove("/home/jihan/hatiku/elen.ku");
 ```
 
Untuk menjalankan program c tersebut **setiap 3 detik** maka gunakan **_daemon_** dan gunakan perintah `sleep(3)` untuk menjalankannya setiap 3 detik.

## Soal 3
Diberikan file campur2.zip. Di dalam file tersebut terdapat folder “campur2”. 
Buatlah program C yang dapat :

i)  mengekstrak file zip tersebut.

ii) menyimpan daftar file dari folder “campur2” yang memiliki ekstensi .txt ke dalam file daftar.txt. 

Catatan:  

 - Gunakan fork dan exec.

 - Gunakan minimal 3 proses yang diakhiri dengan exec.

 - Gunakan pipe

 - Pastikan file daftar.txt dapat diakses dari text editor


## Soal 4
Dalam direktori /home/[user]/Documents/makanan terdapat file makan_enak.txt yang berisikan daftar makanan terkenal di Surabaya. Elen sedang melakukan diet dan seringkali tergiur untuk membaca isi makan_enak.txt karena ngidam makanan enak. Sebagai teman yang baik, Anda membantu Elen dengan membuat program C yang berjalan setiap 5 detik untuk memeriksa apakah file makan_enak.txt pernah dibuka setidaknya 30 detik yang lalu (rentang 0 - 30 detik).
Jika file itu pernah dibuka, program Anda akan membuat 1 file makan_sehat#.txt di direktori /home/[user]/Documents/makanan dengan '#' berisi bilangan bulat dari 1 sampai tak hingga untuk mengingatkan Elen agar berdiet.

Contoh:
File makan_enak.txt terakhir dibuka pada detik ke-1

Pada detik ke-10 terdapat file makan_sehat1.txt dan makan_sehat2.txt

Catatan: 

 - dilarang menggunakan crontab
 
 - Contoh nama file : makan_sehat1.txt, makan_sehat2.txt, dst

**_Jawaban:_**

Terdapat file **makan_enak.txt** pada direktori /home/[user]/Documents/makanan, apabila file **makan_enak.txt** tersebut pernah dibuka antara _rentang waktu 0-30 detik_, maka program C akan membuat 1 file dengan nama **makan_sehat#.txt** setiap _5 detik_ .

Menggunakan `<sys/stat.h>` header yang digunakan oleh **stat()** untuk mendapatkan informasi dari atribut pada structure.

Menggunakan `<time.h>` header agar dapat memanggil fungsi **difftime()**.

```c
struct stat makan;
stat("/home/jihan/Documents/makanan/makan_enak.txt", &makan);
time_t waktu_file = makan.st_atime;
time_t waktu_now = time(NULL);
```
 - memanggil fungsi stat untuk menyimpan seluruh informasi pada file **makan_enak.txt** yang disimpan pada atribut **makan**
 - membuat variabel **waktu_file** dan **waktu_now** untuk menyimpan informasi waktu terakhir file **makan_enak.txt** diakses dan current time.
 - `waktu_file = makan.st_atime;` untuk mendapatkan waktu terakhir file **makan_enak.txt** telah dibuka
 - `waktu_now = time(NULL);` untuk mendapatkan waktu sekarang pada server
 
```c
double rangew = difftime(waktu_now, waktu_file);
```
 - memanggil fungsi **difftime()** untuk menghitung perbedaan waktu antara waktu sekarang pada server dan waktu terakhir file **makan_enak.txt** telah dibuka (waktu_now - waktu_file). Lalu disimpan pada variabel **rangew**.

```c
if(rangew >= 0 && rangew <= 30)
	{
		pid_t child = fork();
		int status = 0;
		char namafile[20];
                chdir("/home/jihan/Documents/makanan");
		if (child == 0){
		 sprintf(namafile, "makan_sehat%d.txt", counter);
		 char *argv[3] = {"touch", namafile, NULL};
		 execv("/usr/bin/touch", argv);
		}
		else {
		 while((wait(&status)) > 0);
		 counter++;
		}
	}
```
 - Cek apakah **rangew** terdapat pada interval _0-30 detik_. Apabila iya, maka file **makan_enak.txt** telah dibuka antara rentang waktu 0-30 detik (waktu_file) yang lalu dari current time (waktu_now)
 - Gunakan **fork()**, jalankan child untuk membuat file **makan_sehat#.txt**
 - Sebelumnya telah diinisialisasi `int counter = 1;` sebelum loop. Karena file yang akan dibuat pertama yaitu **makan_sehat1.txt**
 - Child akan membuat file dengan command **touch** 
   ```c
   if (child == 0){
		 sprintf(namafile, "makan_sehat%d.txt", counter);
		 char *argv[3] = {"touch", namafile, NULL};
		 execv("/usr/bin/touch", argv);
		}
   ```
 - Setelah child dieksekusi, maka akan mengeksekusi parent yang akan increment variabel **counter**.
   ```c
   else {
		 while((wait(&status)) > 0);
		 counter++;
		}
   ```

Untuk menjalankan program c tersebut **setiap 5 detik** maka gunakan **_daemon_** dan gunakan perintah `sleep(5)` untuk menjalankannya setiap 5 detik.

## Soal 5
Kerjakan poin a dan b di bawah:

 a. Buatlah program c untuk mencatat log setiap menit dari file log pada syslog ke /home/[user]/log/[dd:MM:yyyy-hh:mm]/log#.log

Ket:

 - Per 30 menit membuat folder /[dd:MM:yyyy-hh:mm]

 - Per menit memasukkan log#.log ke dalam folder tersebut

   ‘#’ : increment per menit. Mulai dari 1

  b. Buatlah program c untuk menghentikan program di atas.

NB: Dilarang menggunakan crontab dan tidak memakai argumen ketika menjalankan program.


