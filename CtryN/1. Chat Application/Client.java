import java.io.IOException;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Scanner;

public class Client{

    public static void main(String args[]){

        final Socket clientSocket;
        final PrintWriter out;
        final BufferedReader in;
        final Scanner sc = new Scanner(System.in);

        try {
            clientSocket = new Socket("127.0.0.1",4000);  
            in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
            out = new PrintWriter(clientSocket.getOutputStream());

            Thread sender = new Thread(new Runnable() {
                String msg;
                @Override
                public void run(){
                    while(true){
                        msg = sc.nextLine();
                        out.println(msg);
                        out.flush();
                    }
                }
            });
            sender.start();

            Thread receiver = new Thread(new Runnable() {
                String msg;
                @Override
                public void run(){
                    try {
                        msg = in.readLine();
                        while(msg!=null){
                            System.out.println(msg);
                            msg = in.readLine();
                        }
                        out.close();
                        clientSocket.close();                
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                } 
            });
            receiver.start();

            
        } catch (IOException e) {

            e.printStackTrace();

        }

    }

}