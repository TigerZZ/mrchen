import java.io.File;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.transform.OutputKeys;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.NodeList;
public class xmlResolve {
	public static void main(String[] args) throws Exception{
		/*解析xml文件；
		DocumentBuilderFactory bf = DocumentBuilderFactory.newInstance();
		
		DocumentBuilder builder = bf.newDocumentBuilder();
		
		Document doc = builder.parse(new File("D:"+File.separator+"main.xml"));
		
		NodeList nl = doc.getElementsByTagName("linkname");
		
		for (int i = 0; i < nl.getLength(); i++) {
			
			Element e = (Element)nl.item(i);
		
			System.out.println(	e.getElementsByTagName("name").item(0).getFirstChild().getNodeValue());
			
			System.out.println(	e.getElementsByTagName("address").item(0).getFirstChild().getNodeValue());
	}*/
		
		
		//生产XML
		
		DocumentBuilderFactory bf = DocumentBuilderFactory.newInstance();
		DocumentBuilder builder = bf.newDocumentBuilder();
		Document doc = builder.newDocument();//创建一个新的XML文档
		//定义各个节点
		Element address = doc.createElement("address");
		Element linkname = doc.createElement("linkname");
		Element name = doc.createElement("name");
		Element email = doc.createElement("email");
		//各自属性
		name.appendChild(doc.createTextNode("陈苗荣"));
		email.appendChild(doc.createTextNode("502435856@qq.com"));
		//逻辑结构
		linkname.appendChild(email);
		linkname.appendChild(name);
		address.appendChild(linkname);
		doc.appendChild(address);		
			
		TransformerFactory tf  = TransformerFactory.newInstance();
		Transformer t = tf.newTransformer();
		t.setOutputProperty(OutputKeys.ENCODING, "UTF-8");
		
		DOMSource source  = new DOMSource(doc);
		
		
		StreamResult result = new StreamResult(new File("D:"+File.separator+"new.xml"));
		t.transform(source, result);
		
}
}
