import ReaderPackage.*;
import java.io.IOException;

public class Main
{
    public static void main(String[] args)
    {
        try
        {
        System.out.print( "\nPodaj int: " );
        System.out.println( Reader.readInt() );


        System.out.print( "\nPodaj double: " );
        System.out.println( Reader.readDouble() );


            System.out.print("\nPodaj Hex: ");
            System.out.println(Reader.readHex());
        }

        catch ( IOException e )
        {
            System.out.println("Error: " + e.getMessage());
        }

    }
}