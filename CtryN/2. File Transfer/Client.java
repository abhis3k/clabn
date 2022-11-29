import java.io.*;
import java.net.*;

public class Client{
    private static DataInputStream dataInputStream = null;
    private static DataOutputStream dataOutputStream = null;

    public static void main(String[] agrs){
        try(Socket socket = new Socket("localhost",8000);){
            dataInputStream = new DataInputStream(socket.getInputStream());
            dataOutputStream = new DataOutputStream(socket.getOutputStream());

            sendFile("/Users/abhisekr/Downloads/text.txt");
            dataInputStream.close();
            dataOutputStream.close();

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static void sendFile(String path) throws Exception{
        int bytes=0;
        File file = new File(path);
        FileInputStream fileInputStream = new FileInputStream(file);

        dataOutputStream.writeLong(file.length());
        byte[] buffer = new byte[4*1024];

        while((bytes=fileInputStream.read(buffer))!=-1){
            dataOutputStream.write(buffer,0,bytes);
            dataOutputStream.flush();
        }
        fileInputStream.close();
    }
}