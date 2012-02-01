package cmr.android;

import android.app.Activity;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.ProgressBar;

public class ProgressBarActivity extends Activity {

	Button mButton;
	ProgressBar mBar;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		setContentView(R.layout.progressbar);
		mButton = (Button)findViewById(R.id.beginbutton);
		mBar = (ProgressBar)findViewById(R.id.progressBar1);
		mBar.setMax(200);
		mButton.setOnClickListener(new BeginOnClickListener());
	}

	
	class BeginOnClickListener implements OnClickListener
	{
		public void onClick(View v) {
			handler.post(updateThread);
		}
	}
	
	Handler handler = new Handler(){
		public void handleMessage(Message msg) {
			mBar.setProgress(msg.arg1);
			System.out.println(msg.arg1);
			if(msg.arg1 < 100)//��С��100��ʱ�򣬽��̼߳������������ȥ
					handler.post(updateThread);
			else//�����Ƴ����������е��߳�
				handler.removeCallbacks(updateThread);
		}
	};
	Runnable updateThread  = new Runnable() {//һ���߳��࣬��ҪΪ�˸��½������̣߳�
		int i = 0;
		public void run() {
			i+=10;
			Message msg = handler.obtainMessage();
			msg.arg1 = i;
			try {
				Thread.sleep(1000);
			} catch (Exception e) {
				e.printStackTrace();
			}
				handler.sendMessage(msg);//��HandleMessageʹ��
			}
	};
}
