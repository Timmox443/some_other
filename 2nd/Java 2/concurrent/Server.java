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
                  
                
                
                // handle multiple client requests in different threads
                new Thread(new Runnable() {
                    public void run() {
                        
                        clientHandler(socket);
                      
                        
                    }
                }).start();
                long end00 = System.currentTimeMillis();
                System.out.println("Elapsed time in milliseconds: :" + (end00-start00));
            }
                    
            } catch (IOException ioe) {
            ioe.printStackTrace();
        } 
    }
            
    
    private static void clientHandler(final Socket socket) {
        
        try (
            final PrintWriter writeToClient = new PrintWriter(new OutputStreamWriter(socket.getOutputStream(), StandardCharsets.UTF_8));   
        ) {
            while (true) {
                //System.out.println(" ");
                System.out.println("Current Thread ID: "+ Thread.currentThread().getName());
                break;
            }
        
            
        } catch (IOException ioe) {
            ioe.printStackTrace();
        } 

        try {
            socket.close();
        } catch (IOException ioe) {
           ioe.printStackTrace();
        }
    }

    public static void main(String args[]) {
        
        
        Server server = new Server(5000);
        
        
    }
}


