package cmr.android;

import android.R.integer;
import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.ViewDebug.IntToString;
import android.widget.BaseAdapter;
import android.widget.TextView;

public class MyAdapter extends BaseAdapter {
	private LayoutInflater inflater;
	private int []  items;
	
	public MyAdapter(Context context, int [] items)
	{
		inflater = LayoutInflater.from(context);
		this.items = items;
	}
	@Override
	public int getCount() {
		// TODO Auto-generated method stub
		return items.length;
	}

	@Override
	public Object getItem(int arg0) {
		// TODO Auto-generated method stub
		return items[arg0];
	}

	@Override
	public long getItemId(int arg0) {
		// TODO Auto-generated method stub
		return arg0;
	}

	@Override
	public View getView(int arg0, View arg1, ViewGroup arg2) {
		ViewHolder holder;
		if (arg1 == null) {
			arg1 = inflater.inflate(R.layout.learnpoint, null);
			holder = new ViewHolder();
			holder.mTextView = (TextView)arg1.findViewById(R.id.textView1);
		}
		else
			holder = (ViewHolder)arg1.getTag();	
		holder.mTextView.setText(items[arg0]);
		return arg1;
	}

	private class ViewHolder
	{
		TextView mTextView;
	}
	
	
	
}
