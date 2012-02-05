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
		/*����xml�ļ���
		DocumentBuilderFactory bf = DocumentBuilderFactory.newInstance();
		
		DocumentBuilder builder = bf.newDocumentBuilder();
		
		Document doc = builder.parse(new File("D:"+File.separator+"main.xml"));
		
		NodeList nl = doc.getElementsByTagName("linkname");
		
		for (int i = 0; i < nl.getLength(); i++) {
			
			Element e = (Element)nl.item(i);
		
			System.out.println(	e.getElementsByTagName("name").item(0).getFirstChild().getNodeValue());
			
			System.out.println(	e.getElementsByTagName("address").item(0).getFirstChild().getNodeValue());
	}*/
		
		
		//����XML
		
		DocumentBuilderFactory bf = DocumentBuilderFactory.newInstance();
		DocumentBuilder builder = bf.newDocumentBuilder();
		Document doc = builder.newDocument();//����һ���µ�XML�ĵ�
		//��������ڵ�
		Element address = doc.createElement("address");
		Element linkname = doc.createElement("linkname");
		Element name = doc.createElement("name");
		Element email = doc.createElement("email");
		//��������
		name.appendChild(doc.createTextNode("������"));
		email.appendChild(doc.createTextNode("502435856@qq.com"));
		//�߼��ṹ
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
