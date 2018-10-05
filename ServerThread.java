package chat;

import java.net.*;
import java.io.*;
import java.util.*;

public class ServerThread extends Thread {

    protected Socket clientSocket;
    protected ServerSocket serverSocket;
    protected String user;
    private telaServer telaSvr;

    public ServerThread(telaServer telaSvr){
        this.telaSvr = telaSvr;
    }
    
    public ServerSocket startServer (int port) throws IOException{
        serverSocket = new ServerSocket(port);
        telaSvr.gettLog().append("Connection Socket Created\n");
        return serverSocket;
    }
    
    public void waitConnect(){
        try {
            while (true) {
                telaSvr.gettLog().append("Waiting for Connection\n");
                new ServerThread(serverSocket.accept(), telaSvr);
            }
        } catch (IOException e) {
            System.err.println("Accept failed.");
            System.exit(1);
        }
    }

    private ServerThread(Socket clientSoc, telaServer telaSrver) {
        clientSocket = clientSoc;
        telaSvr = telaSrver;
        start();
    }

    public void run() {
        telaSvr.gettLog().append("New Communication Thread Started\n");

        try {
            PrintWriter out = new PrintWriter(clientSocket.getOutputStream(),
                    true);
            BufferedReader in = new BufferedReader(
                    new InputStreamReader(clientSocket.getInputStream()));

            user = in.readLine();
            out.println("Connection Completed");
            String inputLine;
            try {
                while ((inputLine = in.readLine()) != null) {

                    telaSvr.gettLog().append(user + ": " + inputLine+"\n");
                    out.println(inputLine.toUpperCase());

                    if (inputLine.equals("end")) {
                        break;
                    }
                }
            } catch (Exception e) {
                System.out.println("Client exited irregularly");
            }
            out.close();
            in.close();
            clientSocket.close();
        } catch (IOException e) {
            System.err.println("Problem with Communication Server");
            System.exit(1);
        }
    }
}
