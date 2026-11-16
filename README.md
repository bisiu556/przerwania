# Sterownik Ruchu Wahadłowego z Czujnikami (Arduino)

Projekt w języku C++ dla platformy Arduino, realizujący **inteligentne sterowanie ruchem wahadłowym** (np. na zwężeniu drogi, w tunelu lub na jednym pasie ruchu) za pomocą dwóch kierunków, czujników ruchu/obecności (obsługiwanych przez przerwania sprzętowe) oraz sygnalizacji świetlnej.

System działa w pełni automatycznie i bezblokująco, wykorzystując maszynę stanów (`switch-case`) oraz funkcję `millis()`.

---

## 🚦 Jak działa układ?

1. **Stan spoczynku (`stan = 0`):**
   * Oba kierunki mają włączone światło **czerwone**.
   * Układ czeka na wykrycie ruchu z jednej ze stron (czujnik 1 lub czujnik 2).
2. **Uruchomienie ruchu (np. Kierunek 1):**
   * Wykrycie pojazdu/obiektu po stronie 1 (przerwanie sprzętowe) zapala **zielone światło dla kierunku 1** i czerwone dla kierunku 2.
3. **Logika opuszczania strefy (Czujniki):**
   * System monitoruje, kiedy pojazd opuści strefę (odczyt ze stanu czujnika).
   * Po opuszczeniu strefy odliczany jest czas buforowy (np. 5 sekund), po czym następuje przejście do stanu bezpieczeństwa — **oba światła stają się czerwone** na czas ewakuacji zwężenia (2 sekundy), a następnie układ wraca do stanu spoczynku.
4. Symetrycznie działa drugi kierunek (stany 4, 5, 6).

---

## 📌 Podłączenie pinów (Schemat)

Konfiguracja pinów cyfrowych Arduino zdefiniowana w kodzie:

| Urządzenie / Dioda | Pin Arduino | Opis |
| :--- | :--- | :--- |
| **Czujnik 1** | Pin `2` | Wejście czujnika kierunku 1 (obsługuje przerwanie `INT0`) |
| **Czujnik 2** | Pin `3` | Wejście czujnika kierunku 2 (obsługuje przerwanie `INT1`) |
| **Dioda Czerwona 1** | Pin `7` | Czerwone światło dla strony 1 |
| **Dioda Zielona 1** | Pin `8` | Zielone światło dla strony 1 |
| **Dioda Czerwona 2** | Pin `13` | Czerwone światło dla strony 2 |
| **Dioda Zielona 2** | Pin `12` | Zielone światło dla strony 2 |

> *Uwaga: Piny 2 i 3 w płytkach takich jak Arduino Uno / Nano są wymagane do obsługi przerwań sprzętowych (`attachInterrupt`).*

---

## ⏱️ Kluczowe parametry w kodzie

* **Czas opóźnienia / bezpieczeństwa (5 sekund):** Czas w stanie po wykryciu zmiany na czujniku.
* **Czas pełnej czerwieni (2 sekundy):** Okres, w którym oba kierunki mają światło czerwone przed oddaniem pierwszeństwa.
* **Przerwania sprzętowe (`volatile bool`):** Zapewniają natychmiastowe wykrycie impulsu z czujników bez opóźnień wynikających z cyklu pętli `loop`.

---

## 🚀 Jak uruchomić?

1. Sklonuj lub pobierz ten projekt.
2. Otwórz plik w środowisku **Arduino IDE**.
3. Podłącz swoją płytkę Arduino (np. Uno lub Nano) do komputera.
4. Upewnij się, że piny czujników i diod LED są poprawnie spięte zgodnie z tabelą powyżej.
5. Wgraj kod (*Upload*) na mikrokontroler.

---

## 🛠️ Technologie i koncepcje
* **Język:** C++ (Arduino IDE)
* **Kluczowe mechanizmy:** Przerwania sprzętowe (`attachInterrupt`), zmienne ulotne (`volatile`), maszyna stanów (`switch-case`), czas bez blokowania (`millis()`).
