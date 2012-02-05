import java.io.File;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.NodeList;
public class xmlResolve {
	public static void main(String[] args) throws Exception{
		// TODO Auto-generated method stub
		DocumentBuilderFactory bf = DocumentBuilderFactory.newInstance();
		
		DocumentBuilder builder = bf.newDocumentBuilder();
		
		Document doc = builder.parse(new File("D:"+File.separator+"main.xml"));
		
		NodeList nl = doc.getElementsByTagName("linkname");
		
		for (int i = 0; i < nl.getLength(); i++) {
			
			Element e = (Element)nl.item(i);
		
			System.out.println(	e.getElementsByTagName("name").item(0).getFirstChild().getNodeValue());
			
			System.out.println(	e.getElementsByTagName("address").item(0).getFirstChild().getNodeValue());
		}
	}
}
