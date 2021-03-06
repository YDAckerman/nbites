/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * RemoteView.java
 *
 * Created on Jul 27, 2010, 11:40:30 AM
 */

package remote;

import javax.swing.event.DocumentEvent;
import javax.swing.event.DocumentListener;

/**
 *
 * @author Dani
 */
public class RemoteView extends javax.swing.JFrame {
    RemoteController controller;
    RemoteModel model;

    /** Creates new form RemoteView */
    public RemoteView(RemoteController controller, RemoteModel model) {
        initComponents();
        setVisible(true);
        this.controller = controller;
        this.model = model;
    }

    /** This method is called from within the constructor to
     * initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is
     * always regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {
        java.awt.GridBagConstraints gridBagConstraints;

        info = new javax.swing.JPanel();
        robotNameLabel = new javax.swing.JLabel();
        jScrollPane1 = new javax.swing.JScrollPane();
        nameChooser = new javax.swing.JList();
        robotIPLabel = new javax.swing.JLabel();
        ipTextField = new javax.swing.JTextField();
        username = new javax.swing.JTextField();
        usernameLabel = new javax.swing.JLabel();
        Build = new javax.swing.JPanel();
        typePanel = new javax.swing.JPanel();
        typeLabel = new javax.swing.JLabel();
        typeChooser = new javax.swing.JComboBox();
        configureButton = new javax.swing.JButton();
        compileButton = new javax.swing.JButton();
        installButton = new javax.swing.JButton();
        Controller = new javax.swing.JPanel();
        logNaoQiButton = new javax.swing.JButton();
        restartNaoQiButton = new javax.swing.JButton();
        stopNaoQiButton = new javax.swing.JButton();
        shutdownButton = new javax.swing.JButton();
        File = new javax.swing.JPanel();
        fileNamePanel = new javax.swing.JPanel();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setTitle("Remote");
        setMinimumSize(new java.awt.Dimension(500, 400));
        getContentPane().setLayout(new java.awt.GridLayout(2, 2));

        info.setBorder(javax.swing.BorderFactory.createLineBorder(new java.awt.Color(0, 0, 0)));
        info.setMinimumSize(new java.awt.Dimension(150, 58));
        info.setPreferredSize(new java.awt.Dimension(150, 150));
        info.setLayout(new java.awt.GridBagLayout());

        robotNameLabel.setText("Robot Name:");
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 0;
        gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
        gridBagConstraints.insets = new java.awt.Insets(42, 1, 0, 0);
        info.add(robotNameLabel, gridBagConstraints);

        nameChooser.setModel(new javax.swing.AbstractListModel() {
            String[] strings = { "marvin", "slarti", "trillian", "zaphod" };
            public int getSize() { return strings.length; }
            public Object getElementAt(int i) { return strings[i]; }
        });
        nameChooser.setSelectionMode(javax.swing.ListSelectionModel.SINGLE_SELECTION);
        nameChooser.addListSelectionListener(new javax.swing.event.ListSelectionListener() {
            public void valueChanged(javax.swing.event.ListSelectionEvent evt) {
                nameChooserValueChanged(evt);
            }
        });
        jScrollPane1.setViewportView(nameChooser);

        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 3;
        gridBagConstraints.gridy = 0;
        gridBagConstraints.gridheight = 2;
        gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
        gridBagConstraints.ipadx = 175;
        gridBagConstraints.ipady = 146;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.NORTHWEST;
        gridBagConstraints.weightx = 1.0;
        gridBagConstraints.weighty = 1.0;
        info.add(jScrollPane1, gridBagConstraints);

        robotIPLabel.setText("Robot IP:");
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 4;
        gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
        gridBagConstraints.insets = new java.awt.Insets(14, 10, 14, 4);
        info.add(robotIPLabel, gridBagConstraints);

        ipTextField.setMaximumSize(new java.awt.Dimension(2, 2));
        ipTextField.setMinimumSize(new java.awt.Dimension(2, 2));
        ipTextField.setPreferredSize(new java.awt.Dimension(7, 7));
        ipTextField.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                ipTextFieldActionPerformed(evt);
            }
        });
        ipTextField.addInputMethodListener(new java.awt.event.InputMethodListener() {
            public void caretPositionChanged(java.awt.event.InputMethodEvent evt) {
            }
            public void inputMethodTextChanged(java.awt.event.InputMethodEvent evt) {
                ipTextFieldInputMethodTextChanged(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 3;
        gridBagConstraints.gridy = 3;
        gridBagConstraints.gridheight = 2;
        gridBagConstraints.fill = java.awt.GridBagConstraints.BOTH;
        gridBagConstraints.ipady = 24;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.NORTHWEST;
        info.add(ipTextField, gridBagConstraints);

        username.setText(model.NAO_USERNAME);
        username.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                usernameActionPerformed(evt);
            }
        });
        username.addInputMethodListener(new java.awt.event.InputMethodListener() {
            public void caretPositionChanged(java.awt.event.InputMethodEvent evt) {
            }
            public void inputMethodTextChanged(java.awt.event.InputMethodEvent evt) {
                usernameInputMethodTextChanged(evt);
            }
        });
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 3;
        gridBagConstraints.gridy = 2;
        gridBagConstraints.gridwidth = java.awt.GridBagConstraints.REMAINDER;
        gridBagConstraints.fill = java.awt.GridBagConstraints.HORIZONTAL;
        info.add(username, gridBagConstraints);

        usernameLabel.setText("Username");
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 2;
        info.add(usernameLabel, gridBagConstraints);

        getContentPane().add(info);

        Build.setBorder(javax.swing.BorderFactory.createLineBorder(new java.awt.Color(0, 0, 0)));
        Build.setPreferredSize(new java.awt.Dimension(150, 150));
        Build.setLayout(new java.awt.GridLayout(0, 1));

        typePanel.setLayout(new java.awt.GridLayout(1, 0));

        typeLabel.setText("Type:");
        typePanel.add(typeLabel);

        typeChooser.setModel(new javax.swing.DefaultComboBoxModel(new String[] { "cross", "straight", "webots" }));
        typeChooser.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                typeChooserActionPerformed(evt);
            }
        });
        typePanel.add(typeChooser);

        Build.add(typePanel);

        configureButton.setText("Configure man");
        configureButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                configureButtonActionPerformed(evt);
            }
        });
        Build.add(configureButton);

        compileButton.setText("Compile man");
        compileButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                compileButtonActionPerformed(evt);
            }
        });
        Build.add(compileButton);

        installButton.setText("Install man");
        installButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                installButtonActionPerformed(evt);
            }
        });
        Build.add(installButton);

        getContentPane().add(Build);

        Controller.setBorder(javax.swing.BorderFactory.createLineBorder(new java.awt.Color(0, 0, 0)));
        Controller.setPreferredSize(new java.awt.Dimension(150, 150));
        Controller.setLayout(new java.awt.GridLayout(0, 1));

        logNaoQiButton.setText("Log NaoQi");
        logNaoQiButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                logNaoQiButtonActionPerformed(evt);
            }
        });
        Controller.add(logNaoQiButton);

        restartNaoQiButton.setText("Restart NaoQi");
        restartNaoQiButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                restartNaoQiButtonActionPerformed(evt);
            }
        });
        Controller.add(restartNaoQiButton);

        stopNaoQiButton.setText("Stop NaoQi");
        stopNaoQiButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                stopNaoQiButtonActionPerformed(evt);
            }
        });
        Controller.add(stopNaoQiButton);

        shutdownButton.setText("Shutdown Nao");
        shutdownButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                shutdownButtonActionPerformed(evt);
            }
        });
        Controller.add(shutdownButton);

        getContentPane().add(Controller);

        File.setBorder(javax.swing.BorderFactory.createLineBorder(new java.awt.Color(0, 0, 0)));
        File.setPreferredSize(new java.awt.Dimension(150, 150));
        File.setLayout(new java.awt.GridLayout(0, 1));

        fileNamePanel.setLayout(new java.awt.GridLayout(1, 0));
        File.add(fileNamePanel);

        getContentPane().add(File);

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void configureButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_configureButtonActionPerformed
        controller.configure((String)typeChooser.getSelectedItem(),
                            (String)nameChooser.getSelectedValue(),
                            (String)ipTextField.getText());
    }//GEN-LAST:event_configureButtonActionPerformed

    private void compileButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_compileButtonActionPerformed
        controller.compile((String)typeChooser.getSelectedItem());
    }//GEN-LAST:event_compileButtonActionPerformed

    private void ipTextFieldActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_ipTextFieldActionPerformed
    }//GEN-LAST:event_ipTextFieldActionPerformed

    private void typeChooserActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_typeChooserActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_typeChooserActionPerformed

    private void stopNaoQiButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_stopNaoQiButtonActionPerformed
        model.setUsername(username.getText());
        controller.stopNaoQi(ipTextField.getText());
    }//GEN-LAST:event_stopNaoQiButtonActionPerformed

    private void restartNaoQiButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_restartNaoQiButtonActionPerformed
        model.setUsername(username.getText());
        controller.restartNaoQi(ipTextField.getText());
    }//GEN-LAST:event_restartNaoQiButtonActionPerformed

    private void installButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_installButtonActionPerformed
        controller.install((String)typeChooser.getSelectedItem());
    }//GEN-LAST:event_installButtonActionPerformed

    private void nameChooserValueChanged(javax.swing.event.ListSelectionEvent evt) {//GEN-FIRST:event_nameChooserValueChanged
        model.setRobot((String)nameChooser.getSelectedValue());
    }//GEN-LAST:event_nameChooserValueChanged

    private void shutdownButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_shutdownButtonActionPerformed
        model.setUsername(username.getText());
        controller.shutdownRobot(ipTextField.getText());
    }//GEN-LAST:event_shutdownButtonActionPerformed

    private void usernameActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_usernameActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_usernameActionPerformed

    private void usernameInputMethodTextChanged(java.awt.event.InputMethodEvent evt) {//GEN-FIRST:event_usernameInputMethodTextChanged
        model.setUsername(username.getText());
    }//GEN-LAST:event_usernameInputMethodTextChanged

    private void ipTextFieldInputMethodTextChanged(java.awt.event.InputMethodEvent evt) {//GEN-FIRST:event_ipTextFieldInputMethodTextChanged
        model.setHost(ipTextField.getText());
    }//GEN-LAST:event_ipTextFieldInputMethodTextChanged

    private void logNaoQiButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_logNaoQiButtonActionPerformed
        model.setUsername(username.getText());
        controller.logNaoQi(ipTextField.getText());
    }//GEN-LAST:event_logNaoQiButtonActionPerformed


    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JPanel Build;
    private javax.swing.JPanel Controller;
    private javax.swing.JPanel File;
    private javax.swing.JButton compileButton;
    private javax.swing.JButton configureButton;
    private javax.swing.JPanel fileNamePanel;
    private javax.swing.JPanel info;
    private javax.swing.JButton installButton;
    private javax.swing.JTextField ipTextField;
    private javax.swing.JScrollPane jScrollPane1;
    private javax.swing.JButton logNaoQiButton;
    private javax.swing.JList nameChooser;
    private javax.swing.JButton restartNaoQiButton;
    private javax.swing.JLabel robotIPLabel;
    private javax.swing.JLabel robotNameLabel;
    private javax.swing.JButton shutdownButton;
    private javax.swing.JButton stopNaoQiButton;
    private javax.swing.JComboBox typeChooser;
    private javax.swing.JLabel typeLabel;
    private javax.swing.JPanel typePanel;
    private javax.swing.JTextField username;
    private javax.swing.JLabel usernameLabel;
    // End of variables declaration//GEN-END:variables

}
