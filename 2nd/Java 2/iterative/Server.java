import java.io.*;
import java.net.*;
import java.nio.charset.StandardCharsets;

public class Server {
    //initialize socket and input stream
    private Socket socket = null;
    private ServerSocket server = null;
    private DataInputStream in = null;


    public Server(int port) {

        try {
            server = new ServerSocket(port);
            System.out.println("Server started");
            System.out.println("Waiting for a client ...");
            
            while(true){
                socket = server.accept();
                long start00 = System.currentTimeMillis();
                
                System.out.println("Connected to Client: " );
                  
                clientHandler(socket);
                
                long end00 = System.currentTimeMillis();
                System.out.println("Elapsed time in milliseconds: :" + (end00-start00));
                
            }
                    
            } catch (IOException ioe) {
            ioe.printStackTrace();
        } 
    }
            
    
    private static void clientHandler(final Socket socket) {
        
        int total = 0;
        for(int i = 0; i < 9000; i++){
            
            total += total + i;
    
        }
        System.out.println("Total: " + total);

        try {
            socket.close();
        } catch (IOException ioe) {
           ioe.printStackTrace();
        }
    }

    public static void main(String args[]) {
        
        long start00 = System.currentTimeMillis();
        Server server = new Server(5000);
        
        long end00 = System.currentTimeMillis();
        System.out.println("Elapsed time in milliseconds: :" + (end00-start00));
        
        
        
    }
}


