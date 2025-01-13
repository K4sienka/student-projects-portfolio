package ReaderPackage;

import java.io.IOException;
public class Reader
{
    private static char mC = '\0';
    private static boolean ungetted = false;


    /**
     * Reads one character from the input stream System.in
     * @return  returns read character
     * or @return one previous read char
     * only one char could be ungetted
     * in calse of IOException returns character with code 0
     */
    public static char getChar ()  //zwraca pobrany znak
    {
        try {
            if (!ungetted) {
                mC = (char) System.in.read();
            } else
                ungetted = false;

            return mC;

        }
        catch( IOException e )
            {
                return '\0';
            }

    }


/**
 * Returns one character to the input for reloading. Only one char could be returned!
 * @param c - zwracany znak do ponownego odczytu
 */
        public static void ungetChar( char c ) //zwraca znak z strumienia
        {
            mC = c;
            ungetted = true;
        }

/**
 * Reads the integer value written in char case
 * @return the value of integer  number
 */
        public static int readInt()  //do czytania calkowitych
        {
            boolean znak = getSign();
            int number = readNum(); //wczytanie liczby

            return znak ? -number : number;  //jesli minus to go dodac
        }


/**
 * Reads the double value written in char case
 * @return the value of double  num
 */
        public static double readDouble()  //do czytanie dziesietnych
        {
            skipSpaces();

            boolean znak = getSign(); //sprawdzamy znak liczby

            double wynik = readNum(); //czesc calkowita

            if (getChar() == '.' )  //jesli jest .
            {
                double ulamek = readNum();          //wczytuje czesc dziesietna
                while (ulamek >= 1)     ulamek *= 0.1; //przesuwamy przecinek dopoki cala czesc dziesietna nie bedzie na swoim miejscu

                wynik += ulamek; //dodanie czesci dziesietnej do liczby
            }
            else ungetChar(getChar()); //jesli nie ma to przywraca

            return znak ? -wynik : wynik; //jesli byl minus to go dodaje
        }


/**
 * Reads the hexadecimal value written in char case.
 * @throws IOException in case of wrong hexadecimal number prefix 0X, 0x
 *         IOException( "Wrong hexadecimal prefix! Shoud be 0x or 0X" );
 * @return value of proper hexadecimal value
 */
        public static int readHex() throws IOException //czy to 16stkowa
        {
            skipSpaces();

            char c = getChar(); //pobieramy znak
            if (c != '0')  //najpierw musi byc 0
            {
                ungetChar(c);       //jesli nie ma to blad
                throw new IOException("Wrong hexadecimal prefix! Should be 0x or 0X");
            }

            c = getChar(); //kolejny znak
            if (c != 'x' && c != 'X')  //jesli po 0 nie ma x
            {
                ungetChar(c);           //znow blad
                throw new IOException("Wrong hexadecimal prefix! Should be 0x or 0X");
            }

            int number = 0;
            while (isHexDigit(c = getChar()))
                number = 16 * number + charHexDigit2Int(c); //konwersja

            ungetChar(c);  //przywrocenie znaku ktory nie jest liczba
            return number; //zwraca liczbe
        }





//================ P R I V A T E INTERFACE ==========================================
        private static int readNum() // czyta liczbe calkowita ze znakiem (pomija biale znaki przed zznakiem)
        {
            skipSpaces();
            int number=0;
            char c;
            while( isDecDigit( c=getChar() ) )
                number=number*10 +charDecDigit2Int(c); //konwersja

            ungetChar(c); //cofnij znak
            return number;
        }

        private static boolean getSign()  // return true or false; true - in case '-' (pomija biale znaki przed)
        {
            skipSpaces(); // Pomijanie białych znaków
            char c = getChar(); //pobranie znaku
            if (c == '-')        //jesli - to true,
            {
                return true;
            } else if (c == '+') //jesli + to false
            {
                ungetChar(c);
                return false;
            } else                  //jesli nie to znaczy ze jakis znak i cofamy to strumienia
            {
                ungetChar(c);
                return false;
            }
        }


        private static void skipSpaces() // nic nie zwraca, pomija biale znaki (wszystkie: spacje tabulatory, nowe linie - oba zanki)
        {
            char c = getChar();     //pobierz znak
            while( c == 32 || c == 9 || c == 10 || c == 13 ) //32 spacja, 9 tabulator, 10 i 13 nowa linia (CRLF)
                c = getChar();  //pomija poki trafia na te znaki
            ungetChar( c );     //odrzuca znak inny niz biale do strumienia zeby znow mogl byc wczytany
        }


//FUNKCJE JEDNOLINIJKOWE DO WCZYTU 16STOKOWYCH

        private static boolean  isDecDigit( char c )// logiczna - jedna linijka kodu
        {
            return ( c>='0' && c<='9' ); //czy liczba od 0 do 10
        }

        private static boolean  isHexDigit( char c )// logiczna, jedna linijka kodu
        {
            return ( isDecDigit( c ) || isHexLetter( c ) ) ; //czy to liczba 16stkowa ( 0-10 lub a-f)
        }

        private static char  upperCase( char c ) // zamienia male na duze ale tylko dla a..f,  jedna linijka kodu
        {
            return ( c>='a' && c <='f' ) ? (char)( c-32 ) : c ; //zamiana malych liter na duze
        }

        private static boolean isHexLetter( char c )// logiczna ,jedna linijka kodu
        {
            return ( c >='A' && c <='F' ) || ( c>= 'a' && c<= 'f' ); //czy 16stkowa
        }

        private static int charDecDigit2Int( char c )// zwraca wartosc cyfry dzisietnej, jedna linijka kodu
        {
            return c-'0' ; // -48 z kodu ASCII
        }

        private static int charHexDigit2Int( char c )// zwraca wartosc cyfry szesnastkowej, jedna linijka kodu
        {
            return isDecDigit(c) ? charDecDigit2Int(c) : ( isHexLetter(c) ? ( c >= 'a' ? charDecDigit2Int( upperCase(c) ) - 7 : charDecDigit2Int(c) ) : 0 );
            //jezeli znak to cyfra 10 to wywolanie funkcji, jesli to litera to obsluga a-f, jesli ani to ani to to 0
        }


    } //end of class