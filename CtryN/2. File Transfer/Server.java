import java.io.*;
import java.net.*;

public class Server {
    private static DataInputStream dataInputStream = null;
    private static DataOutputStream dataOutputStream = null;

    public static void main(String[] args){
        try(ServerSocket serverSocket = new ServerSocket(8000)) {
            Socket socket = serverSocket.accept();
            dataInputStream = new DataInputStream(socket.getInputStream());
            dataOutputStream = new DataOutputStream(socket.getOutputStream());

            rcvFile("text.txt");

            dataInputStream.close();
            dataOutputStream.close();
            
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static void rcvFile(String fileName) throws Exception{
        int bytes = 0;
        File file = new File(fileName);
        FileOutputStream fileOutputStream = new FileOutputStream(file);

        long size = dataInputStream.readLong();
        byte[] buffer = new byte[4*1024];

        while(size>0 && (bytes=dataInputStream.read(buffer,0,(int)Math.min(buffer.length, size)))!=-1){
            fileOutputStream.write(buffer,0,bytes);
            size -= bytes;
        }
        fileOutputStream.close();
    }
}
