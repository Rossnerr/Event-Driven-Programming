   M S B A M L   `   `   `  ����D  @EDP_Lab.6, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null'clr-namespace:EDP_Lab._6
EDP_Lab._6  5   	       EDP_Lab._6.AddTaskDialog   5   	   \ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    5   	   R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5   	   @d2http://schemas.microsoft.com/expression/blend/2008     5   	   Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5   	   *localclr-namespace:EDP_Lab._6     5   	     � Title$  Add Task��5   	   $	��250��6   $	��300��6'   .��5
      � $��Center=�6   $��Center=�6(    � RowDefinitions 5   
   �� 5      $��25 �6   �� 5      $��29 �6   �� 5      $��34 �6   �� 5      $��84 �6   �� 5      $��28 �6    � ColumnDefinitions 5   
   �� 5      $��75 �6   �� 5      $��75 �6   �� 5       $	��125 �6   .+�5$   
   �� $��0��6   $��0��6   $��Title:��6-   �� 5&   
   -   5        $��	TaskTitle��5&      $��0��6#   $��1��60   $��2��6@   �� 5(   
   $��1��6   $��0��6   $��	Priority:��6-   $��0,3,0,0q�6A   �� 5*   
   -   5        $��TaskPriority��5*      $��1��6'   $��1��64   $��2��6D    �� SelectedIndex$ 0��6X   $��0,3,0,0q�6j   .@�5,      �� 
��� � �.��6.   Low63   �� 5.      
��� ���.��6/   Medium67   �� 50      
���  ��.��6,   High62   52      �� 54   
   $��2��6   $��0��6   $��Description:��6-   $��0,3,0,0q�6D   �� 56   
   -   5        $��TaskDescription��56      $��3��6)   $��0��66   $��3��6F    �� TextWrapping$
 Wrap=�6Z   $��0,3,0,0q�6n   �� 58   
   -   5        $��
OkayButton��58      $��4��6#   $��0��60   $
��Okay��6@   $��0,3,2,0q�6O   6`   �� 5:   
   -   5        $��CancelButton��5:      $��4��6%   $��1��62    �� IsCancel . $��Cancel��6R   $��2,3,0,0q�6c   5<      5>      