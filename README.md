



# DOM PARSER PROJECT

Bu proje; ham HTML metinlerini analiz eden, bellek üzerinde hiyerarşik bir ağaç yapısına dönüştüren ve bu yapıyı interaktif bir terminal paneli üzerinden yöneten bir **DOM (Document Object Model) Motoru simülasyonudur**.

Proje, standart kütüphanelerden bağımsız olarak, **saf C dili** ile geliştirilmiş hibrit bir veri mimarisi üzerine kurulmuştur.

---

# 🧠 Sistem Mimarisi ve Veri Akışı

Proje, üç ana katmanın birleşimiyle **"Full-Stack" bir terminal uygulaması** gibi çalışır:

---

## 1. Tokenizasyon ve Veri Yapılandırması

Süreç, HTML dosyasının karakter karakter taranmasıyla başlar.

Bu aşamada:

- **Ayrıştırma (Parsing):** Etiketler, ID'ler ve içerikler birbirinden ayrılır.
- **Yığıt (Stack) Yönetimi:** Stack yapısı kullanılarak açılış ve kapanış etiketleri eşleştirilir, böylece iç içe geçmiş (*nested*) yapılar hatasız bir şekilde hiyerarşiye aktarılır.

---

## 2. Hibrit Bellek Yönetimi (Tree & Hash)

Verimli bir veri erişimi için iki temel yapı eşzamanlı çalışır:

- **N-Ary Tree:** HTML'in ebeveyn-çocuk ilişkisini korumak için kullanılır.  
  Her düğüm, dalların durumunu (açık/kapalı) kontrol eden bir `is_expanded` bayrağına sahiptir.

- **Hash Table:** DOM elemanlarına ID üzerinden `O(1)` hızında ulaşmayı sağlar.  
  Çakışmalar **Chaining** yöntemiyle yönetilir.

---

## 3. İnteraktif Dashboard ve Manipülasyon

Kullanıcıya sunulan terminal arayüzü (**Dashboard**), projenin en özgün kısmıdır:

- **Görselleştirme:** Ağaç yapısı, derinlik göstergeleri ve `[+] / [-]` ikonlarıyla daraltılıp genişletilebilir (*Collapsible Tree*).
- **Dinamik İşlemler:** Terminal üzerinden `append`, `delete` ve `find` komutları canlı olarak yürütülür.
- **Veri Kalıcılığı:** Bellekte yapılan tüm değişiklikler `save` komutuyla standart bir HTML dosyasına (`output.html`) aktarılır.

---

# 🚀 Kullanılan Veri Yapıları

- Stack
- Queue
- Hash Table
- N-Ary Tree

---

# 💻 Geliştirme Dili

- **C Programming Language**

---

# 📂 Çıktı

Program çalıştırıldığında:

- HTML parse edilir
- DOM ağacı oluşturulur
- Terminal dashboard üzerinden yönetilir
- Güncel yapı `output.html` dosyasına kaydedilir


---

# 👥 Ekip Üyeleri

- Zeynep Alperen — HTML Parser, Stack, Queue
- Osman Cubukcu — N-ary Tree, Data Structures
- Seydi — Hash Table
- Yigit Arslan — DOM Operations, DFS/BFS

---

# ⚙️ Derleme ve Çalıştırma

## Manuel Derleme (GCC ile)
```bash
gcc main.c data_structures.c dom_parser.c dom_operations.c hash_table.c -o dom_editor
./dom_editor
```

## Docker ile Çalıştırma
```bash
docker-compose run --rm dom-editor
```

# 🖥️ Kullanılabilir Komutlar

| Komut | Açıklama |
|---|---|
| `find <id>` | ID'ye göre eleman arar ve işaretler |
| `toggle <id>` | Elemanı açar veya kapatır |
| `append <parent_id> <tag> <id>` | Yeni eleman ekler |
| `delete <id>` | Elemanı ve alt dallarını siler |
| `save` | Ağacı output.html olarak kaydeder |
| `exit` | Programdan çıkar |

---

# 📋 Bağımlılıklar

- GCC derleyici (manuel derleme için)
- Docker Desktop (Docker ile çalıştırma için)

