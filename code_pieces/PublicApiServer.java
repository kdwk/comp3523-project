import com.sun.net.httpserver.HttpServer;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpExchange;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;

public class PublicApiServer {

    public static void main(String[] args) throws IOException {
        // Create an HTTP server on port 8080
        HttpServer server = HttpServer.create(new InetSocketAddress(8080), 0);
        server.createContext("/compute", new ComputeHandler());
        server.setExecutor(null); // Creates a default executor
        server.start();
        System.out.println("Server started on port 8080");
    }

    static class ComputeHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String response;
            if ("GET".equals(exchange.getRequestMethod())) {
                // Read query parameters (e.g., ?input=1000000)
                String query = exchange.getRequestURI().getQuery();
                String input = query != null ? query.split("=")[1] : "0";

                try {
                    // Simulate a resource-intensive computation
                    int number = Integer.parseInt(input);
                    long result = performHeavyComputation(number);
                    response = "Computation result: " + result;
                } catch (Exception e) {
                    response = "Error: " + e.getMessage();
                }

                exchange.sendResponseHeaders(200, response.length());
            } else {
                response = "Unsupported method";
                exchange.sendResponseHeaders(405, response.length());
            }

            // Send the response
            OutputStream os = exchange.getResponseBody();
            os.write(response.getBytes());
            os.close();
        }

        // Simulate a resource-intensive computation
        private long performHeavyComputation(int num) {
            long total = 0;
            for (int i = 0; i < num; i++) {
                total += i;
            }
            return total;
        }
    }
}
