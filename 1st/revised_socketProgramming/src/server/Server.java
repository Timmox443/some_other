package server;

import java.io.BufferedInputStream; //reads information from the stream
import java.io.DataInputStream; //enables software to take use of the input stream for reading simple data
import java.io.IOException; //When an input or output operation fails or is misinterpreted,
// an input/output exception (I/O) is thrown.
import java.net.ServerSocket; //The ServerSocket Class is for implementing the server's end of a
// client/server Socket Connection in a platform-independent manner.
import java.net.Socket; //Since each instance of the socket class is uniquely
// bound to a single distant host, establishing a connection to a different host requires the creation of a new socket object.

public class Server {
    //Perform the necessary setup on the input stream as well as socket.
    private Socket socket = null;// assigns no value to the socket
    private ServerSocket server = null; //assigns no value to the  serversocket
    private DataInputStream in = null; // as well as  the channel is assigned a null value


    public Server(int port) {

        try { //generates a new storage space on the server
            server = new ServerSocket(port);// initiates and show the server has just started
            System.out.println("Server started");// this will be displayed to indicate that the server has just begin
            System.out.println("Waiting for a client ...");
            socket = server.accept();
            System.out.println("Client accepted");// this show that connection between client and server is complete
            in = new DataInputStream(new BufferedInputStream(socket.getInputStream()));// receives the output from client
            String line = ""; // string that takes input and interprets it
// Until you type "Over," keep reading.
            //and until the connection is disconnected
            while (!line.equals("Over")) {
                try {
                    line = in.readUTF(); //reads the encoding
                    System.out.println(line); //it will print the output


                } catch (IOException i) { // try and catch any errors
                    System.out.println(i); //wii print any errors if available
                }
            }
            System.out.println("Closing connection");// this message will be displayed if the  is broken
            socket.close();// the socket is close
            in.close(); // the input will bw closed
        } catch (
                IOException i) { // while closing the connection it will try to check m for errors
            System.out.println(i); // will print errors if available
        }

    }

    public static void main(String args[]) {
        Server server = new Server(5000);
    }
}


