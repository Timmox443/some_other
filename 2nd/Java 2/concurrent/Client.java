import java.io.*;
import java.net.*;
import java.util.*;
import java.time.*;

public class Client{

    // initialize socket and input output streams
    private Socket socket = null;
    private DataInputStream input = null;
    private DataOutputStream out = null;
    Thread t;

    // constructor to put ip address and port
    public Client(String address, int port) {
        try {
            /**
             * Creates the socket and connects it to the IP address and port
             */
            long start0 = System.currentTimeMillis();
            socket = new Socket(address, port);
            System.out.println("connected");
            System.out.println("Hello, My name is Samuel!");
            
            for(int i = 0; i < 100; i++) {
                long start1 = System.currentTimeMillis();
                
                t = new Thread();
                t.start();
               
                long end1 = System.currentTimeMillis();
                System.out.println("Thread " + (i+1) + ":" + (end1-start1));
            }
            
            long end0 = System.currentTimeMillis();
            
            System.out.println("Elapsed time in milliseconds: :" + (end0-start0));
            
            

        } catch (UnknownHostException u) {
            System.out.println(u);
        } catch (IOException i) {
            System.out.println(i);
        }
        

    }

    public static void main(String args[]) {
        Client client = new Client("127.0.0.1", 5000);
    }
}
