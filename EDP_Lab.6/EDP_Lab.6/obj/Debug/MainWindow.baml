   M S B A M L   `   `   `  ����D  @EDP_Lab.6, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null'clr-namespace:EDP_Lab._6
EDP_Lab._6  5   	       EDP_Lab._6.MainWindow   5   	   \ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    5   	   R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5   	   @d2http://schemas.microsoft.com/expression/blend/2008     5   	   Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5   	   *localclr-namespace:EDP_Lab._6     5   	     � Title$  
To-Do List��5   	    J� SnapsToDevicePixels . $	��500��67   $	��384��6D    � 	Resources 5	       	  tasks � Source � XPath   EDP_Lab._6.StatusConverter  statusConverter"  EDP_Lab._6.PriorityConverter  priorityConverter  TaskTemplate � ColumnDefinitions � RowDefinitions d� 	IsChecked �� XPath	 �� 	Converter��%�  &	        &	 9     &	 L     &	 _     7  7  � 5
   
   $ 	Tasks.xml?�6(   $ 
Tasks/Task��6;     5   
   6      5   
   6"   �� 5   
   .R�5      �  5      �� 5      $��30 �6'   �� 5      $��* �6'    5      �� 5      $��15 �6$   �� 5      $��* �6$   .+�5      �� $��0��6   $��2��6(   $��0��69   $��Center=�6I   $��Center=�6f    6�   �� $
 Done��8	   �� 5      $��0��6   $��1��6)   $
��Bold"�69   ��6K   �� $ Priority��8	  ��6�   �� $
 Name���� 5      $��1��6   $��1��6)   $��0,0,0,5q�69   ��6J   �� $ Description��5      5      5      .��5       � $��Center=�6   $��Center=�6(    5!   
   �� 5"      $	��175 �6   �� 5#      $	��175 �6    5%   
   �� 5&      $	��400 �6   �� 5'      $��30 �6   .+�5*   
   �� -   5        $��TaskListBox��5*      $��0��6%   $��0��62   $��2��6B   $��0,8,0,22q�6�   $��2��6�   ��6V   �� 
 �� Source#
 [  6�   �� 5,   
   -   5        $��	AddButton��5,      $��1��6"   $��0��6/   $��	0,11,2,-8q�6?   $��Add Task��6R   6e   �� 5.   
   -   5        $��DeleteButton��5.      $��1��6%   $��1��62   $��	0,11,2,-8q�6B   $��Delete Task��6V   6l   5/      50      